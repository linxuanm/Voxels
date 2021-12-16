#pragma once

#define BLOCK_AIR 0
#define BLOCK_STONE 1
#define BLOCK_DIRT 2
#define BLOCK_GRASS 3
#define BLOCK_LOG 4
#define BLOCK_WATER 5

namespace Blocks {
    bool isSolid(int block);
};
