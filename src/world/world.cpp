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
    for (int i = -2; i < 3; i++) {
        for (int j = -2; j < 3; j++) {
            chunks[(long) i << 32 | j] = generator.generateChunk(i, j);
        }
    }
}
