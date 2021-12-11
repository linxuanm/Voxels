#pragma once

#include "util/specs.h"

class Chunk {

public:
    Chunk();

//private:
    int blocks[16 * 16 * CHUNK_HEIGHT];
};
