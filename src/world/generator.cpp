#include "generator.h"

#include <iostream>

#include "world/blocks.h"

Generator::Generator() = default;

std::shared_ptr<Chunk> Generator::genChunk(World &w, ChunkPos x, ChunkPos z) {
    std::shared_ptr<Chunk> chunk = std::make_shared<Chunk>(w, x, z);
    BlockRef stonePtr = Blocks::stone.get();
    BlockRef dirtPtr = Blocks::dirt.get();
    BlockRef grassPtr = Blocks::grass.get();

    //TODO: better cache locality
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            for (int h = 0; h < 16; h++) {
                chunk->blocks[h << 8 | i << 4 | j] = stonePtr;
            }
            for (int h = 16; h < 19; h++) {
                chunk->blocks[h << 8 | i << 4 | j] = dirtPtr;
            }
            chunk->blocks[19 << 8 | i << 4 | j] = grassPtr;
        }
    }

    return chunk;
}
