#pragma once

#include <memory>

#include "math/noise.h"
#include "world/chunk.h"

class Generator {

public:
    Generator(uint32_t seed, int inBase, int inVariance);
    std::shared_ptr<Chunk> genChunk(World &w, ChunkPos x, ChunkPos z);

private:
    CompositePerlin perlinNoise;
    int baseHeight;
    int vary;
};
