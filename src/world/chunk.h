#pragma once

#include <cstdint>

#include "util/specs.h"

typedef int32_t ChunkPos;

class Chunk {

public:
    int blocks[CHUNK_HEIGHT * 16 * 16];

    Chunk();
};
