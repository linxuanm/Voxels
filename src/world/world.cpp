#include "world.h"

World::World(): generator(42) {}

std::shared_ptr<Chunk> World::getBlockChunk(int x, int z) {
    return getChunk(x >> 4, z >> 4);
}

std::shared_ptr<Chunk> World::getChunk(ChunkPos x, ChunkPos z) {
    return chunks[(long) x << 32 | z];
}

ChunkMap &World::chunkMap() {
    return chunks;
}

void World::initWorld() {
    chunks[5l << 32 | 6] = generator.generateChunk(5, 6);
}
