#include "generator.h"

#include <iostream>

#include "world/blocks.h"

Generator::Generator(long inSeed): seed(inSeed) {}

std::shared_ptr<Chunk> Generator::generateChunk(ChunkPos x, ChunkPos z) {
    std::shared_ptr<Chunk> chunk = std::make_shared<Chunk>();

    for (int h = 0; h < 20; h++) {
        for (int i = 0; i < 16; i++) {
            for (int j = 0; j < 16; j++) {
                chunk->blocks[h][i][j] = BLOCK_DIRT;
            }
        }
    }

    return chunk;
}
