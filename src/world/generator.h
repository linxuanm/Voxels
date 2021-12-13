#pragma once

#include "world/chunk.h"

class Generator {

public:
    Generator();
    Chunk *generateChunk(ChunkPos x, ChunkPos z);

private:
    long seed;
};
