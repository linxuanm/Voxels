#include "blocks.h"

bool Blocks::isSolid(int block) {
    return block != BLOCK_AIR;
}
