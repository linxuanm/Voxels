#include "world.h"

#include "world/blocks.h"

World::World() = default;

std::shared_ptr<Chunk> World::getChunkAt(const BlockPos &pos) {
    return getChunk(pos.x() >> 4, pos.z() >> 4);
}

std::shared_ptr<Chunk> World::getChunk(ChunkPos x, ChunkPos z) {
    auto iter = chunks.find({x, z});
    if (iter == chunks.end()) return nullptr;

    return iter->second;
}

Chunks &World::getChunks() {
    return chunks;
}

int World::getBlock(const BlockPos &pos) {
    auto chunk = getChunkAt(pos);
    if (chunk == nullptr) return BLOCK_AIR;

    return chunk->getBlockRel({pos.x() & 15, pos.y(), pos.z() & 15});
}

void World::initWorld() {
    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            chunks[{i, j}] = generator.genChunk(*this, i, j);
        }
    }
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

BlockPos World::traceBlock(const glm::vec3 &start, const glm::vec3 &end) {
    return BlockPos{start};
}

BlockPos World::traceBlock(const Camera &cam, float length) {
    glm::vec3 start = cam.getCurrPos();
    glm::vec3 forward = cam.getForward() * length;
    glm::vec3 end = start + forward;

    return traceBlock(start, end);
}
