#pragma once

#include <memory>

#include "world/chunk.h"

class Generator {

public:
    explicit Generator(long seed);
    std::shared_ptr<Chunk> generateChunk(ChunkPos x, ChunkPos z);

private:
    long seed;
};
