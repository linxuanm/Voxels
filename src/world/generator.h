#pragma once

#include <memory>

#include "world/chunk.h"

class Generator {

public:
    Generator();
    std::shared_ptr<Chunk> generateChunk(ChunkPos x, ChunkPos z);

private:
    long seed;
};
