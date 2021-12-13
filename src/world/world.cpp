#include "world.h"

World::World() = default;

std::shared_ptr<Chunk> World::getBlockChunk(int x, int z) {
    return getChunk(x >> 4, z >> 4);
}

std::shared_ptr<Chunk> World::getChunk(ChunkPos x, ChunkPos z) {
    return chunks[(long) x << 32 | z];
}
