#include "blocks.h"

Block::Block(int inId): id(inId) {}

bool Blocks::isSolid(int block) {
    return block != BLOCK_AIR;
}
