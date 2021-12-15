#include "world.h"

World::World(): generator(42) {}

std::shared_ptr<Chunk> World::getBlockChunk(int x, int z) {
    return getChunk(x >> 4, z >> 4);
}

std::shared_ptr<Chunk> World::getChunk(ChunkPos x, ChunkPos z) {
    return chunks[std::make_pair(x, z)];
}

Chunks &World::getChunks() {
    return chunks;
}

void World::initWorld() {
    int a = 0;
    for (int i = -2; i < 3; i++) {
        for (int j = -2; j < 3; j++) {
            chunks[std::make_pair(i, j)] = generator.generateChunk(i, j);
        }
    }
}
