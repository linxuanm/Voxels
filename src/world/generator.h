#pragma once

#include <memory>

#include "world/chunk.h"

class Generator {

public:
    explicit Generator();
    std::shared_ptr<Chunk> genChunk(World &w, ChunkPos x, ChunkPos z);
};
