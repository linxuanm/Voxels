#pragma once

#include <cstdint>

#include "util/specs.h"

typedef int32_t ChunkPos;

class Chunk {

public:
    Chunk();

private:
    int blocks[16 * 16 * CHUNK_HEIGHT];
};
