#include "world.h"

#include "world/blocks.h"

World::World() {}

std::shared_ptr<Chunk> World::getBlockChunk(int x, int z) {
    return getChunk(x >> 4, z >> 4);
}

std::shared_ptr<Chunk> World::getChunk(ChunkPos x, ChunkPos z) {
    return chunks[std::make_pair(x, z)];
}

Chunks &World::getChunks() {
    return chunks;
}

int World::getBlock(const BlockPos &pos) {
    ChunkPos x = pos.x() >> 4;
    ChunkPos z = pos.z() >> 4;

    auto iter = chunks.find({x, z});
    if (iter == chunks.end()) return BLOCK_AIR;

    return iter->second->getBlockRel({pos.x() & 15, pos.y(), pos.z() & 15});
}

void World::initWorld() {
    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            chunks[{i, j}] = generator.genChunk(*this, i, j);
        }
    }
}
