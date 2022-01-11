#include "generator.h"

#include <iostream>

#include "world/blocks.h"

Generator::Generator(uint32_t seed, int inBase, int inVariance)
: perlinNoise(seed, 5, 0.5), baseHeight(inBase), vary(inVariance) {}

std::shared_ptr<Chunk> Generator::genChunk(World &w, ChunkPos x, ChunkPos z) {
    std::shared_ptr<Chunk> chunk = std::make_shared<Chunk>(w, x, z);
    BlockRef stonePtr = Blocks::stone.get();
    BlockRef dirtPtr = Blocks::dirt.get();
    BlockRef grassPtr = Blocks::grass.get();

    int xOff = x << 4;
    int zOff = z << 4;

    //TODO: better cache locality
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            float noise = perlinNoise.genNoise(
                (xOff + i) * 0.01f,
                (zOff + j) * 0.01f
            ) * vary + baseHeight;

            int height = static_cast<int>(glm::round(noise));
            height = glm::clamp(height, 0, CHUNK_HEIGHT);

            for (int h = 0; h < height - 4; h++) {
                chunk->blocks[h << 8 | i << 4 | j] = stonePtr;
            }
            for (int h = height - 4; h < height - 1; h++) {
                chunk->blocks[h << 8 | i << 4 | j] = dirtPtr;
            }
            chunk->blocks[(height - 1) << 8 | i << 4 | j] = grassPtr;
        }
    }

    return chunk;
}
