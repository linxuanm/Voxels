#include "world.h"

#include "world/blocks.h"
#include "math/vec.h"

World::World(): chunkLoader(*this) {}

World::~World() = default;

std::shared_ptr<Chunk> World::getChunkAt(const BlockPos &pos) {
    return getChunk(pos.x() >> 4, pos.z() >> 4);
}

std::shared_ptr<Chunk> World::getChunk(ChunkPos x, ChunkPos z) {
    auto iter = chunks.find({x, z});
    if (iter == chunks.end()) return nullptr;

    return iter->second;
}

Chunks &World::getAndLockChunks() {
    chunkLock.lock();
    return chunks;
}

void World::releaseChunks() {
    chunkLock.unlock();
}

int World::getBlock(const BlockPos &pos) {
    auto chunk = getChunkAt(pos);
    if (chunk == nullptr) return BLOCK_AIR;

    return chunk->getBlockRel({pos.x() & 15, pos.y(), pos.z() & 15});
}

void World::setBlock(int block, const BlockPos &pos) {
    auto chunk = getChunkAt(pos);
    if (chunk == nullptr) return;

    chunk->setBlockRel(block, {pos.x() & 15, pos.y(), pos.z() & 15});
    updateBlock(pos);

    for (auto &i: BlockFace::allFacing) {
        updateBlock(pos.offset(i));
    }
}

void World::initWorld() {
    chunkThread = std::thread{&WorldLoadingThread::execute, chunkLoader};
}

void World::updateBlock(const BlockPos &pos) {
    if (pos.y() < 0 || pos.y() > CHUNK_HEIGHT) return;

    auto chunk = getChunkAt(pos);
    if (chunk == nullptr) return;

    chunk->updateRenderChunk(pos.y() >> 4);
}

void World::breakBlock(const BlockPos &pos) {
    if (pos.y() < 0 || pos.y() > CHUNK_HEIGHT) return;

    auto chunk = getChunkAt(pos);
    if (chunk == nullptr) return;

    BlockPos relPos{pos.x() & 15, pos.y(), pos.z() & 15};

    if (chunk->getBlockRel(relPos) == BLOCK_AIR) return;
    chunk->setBlockRel(BLOCK_AIR, relPos);
    updateBlock(pos);

    /*
     * VBO updating uses flags so multiple update on the same chunk
     * is fine.
     */
    for (auto &i: BlockFace::allFacing) {
        updateBlock(pos.offset(i));
    }
}

RayResult World::trace(const glm::vec3 &pos, const glm::vec3 &dir, float len) {

    if (getBlock(BlockPos{pos}) != BLOCK_AIR) return {true, BlockPos{pos}};

    /*
     * link from stackoverflow which lead to
     * http://www.cse.yorku.ca/~amana/research/grid.pdf
     */
    glm::vec3 curr = pos;
    glm::vec3 step{
        dir.x > 0.0f ? 1.0f : -1.0f,
        dir.y > 0.0f ? 1.0f : -1.0f,
        dir.z > 0.0f ? 1.0f : -1.0f
    };
    glm::vec3 next{
        step.x > 0 ? glm::floor(curr.x + step.x) : glm::ceil(curr.x + step.x),
        step.y > 0 ? glm::floor(curr.y + step.y) : glm::ceil(curr.y + step.y),
        step.z > 0 ? glm::floor(curr.z + step.z) : glm::ceil(curr.z + step.z)
    };

    float deltaX = dir.x == 0 ? FLT_MAX : step.x / dir.x;
    float deltaY = dir.y == 0 ? FLT_MAX : step.y / dir.y;
    float deltaZ = dir.z == 0 ? FLT_MAX : step.z / dir.z;

    float maxX = dir.x == 0 ? FLT_MAX : (next.x - curr.x) / dir.x;
    float maxY = dir.y == 0 ? FLT_MAX : (next.y - curr.y) / dir.y;
    float maxZ = dir.z == 0 ? FLT_MAX : (next.z - curr.z) / dir.z;

    BlockFace::Facing hitFace;

    while (true) {
        if (maxX < maxY) {
            if (maxX < maxZ) {
                curr.x += step.x;
                maxX += deltaX;
                hitFace = step.x > 0 ? BlockFace::WEST : BlockFace::EAST;
            } else {
                curr.z += step.z;
                maxZ += deltaZ;
                hitFace = step.z > 0 ? BlockFace::NORTH : BlockFace::SOUTH;
            }
        } else {
            if (maxY < maxZ) {
                curr.y += step.y;
                maxY += deltaY;
                hitFace = step.y > 0 ? BlockFace::DOWN : BlockFace::UP;
            } else {
                curr.z += step.z;
                maxZ += deltaZ;
                hitFace = step.z > 0 ? BlockFace::NORTH : BlockFace::SOUTH;
            }
        }

        if (glm::distance(pos, curr) > len) {
            return {false, BlockPos{pos}, BlockFace::NORTH};
        };

        BlockPos currVoxel{curr};
        if (getBlock(currVoxel) != BLOCK_AIR) {
            return {true, currVoxel, hitFace};
        }
    }
}

RayResult World::trace(const Camera &cam, float len) {
    glm::vec3 start = cam.getCurrPos();
    glm::vec3 dir = cam.getForward();

    return trace(start, dir, len);
}

bool World::shouldShutDown() {
    return shutDown;
}

void World::quit() {
    shutDown = true;

    chunkThread.join();
}

void World::loadChunk(std::pair<ChunkPos, ChunkPos> pos) {
    chunks[pos] = generator.genChunk(*this, pos.first, pos.second);
}

void World::unloadChunk(std::pair<ChunkPos, ChunkPos> pos) {
    chunks.erase(pos);
}
