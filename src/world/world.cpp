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
    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            chunks[std::make_pair(i, j)] = generator.generateChunk(i, j);
        }
    }
}
