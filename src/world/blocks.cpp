#include "blocks.h"

BlockDef Blocks::air;
BlockDef Blocks::dirt;

Block::Block(int inId, bool inSolid): id(inId), solid(inSolid) {}

bool Block::isSolid() const {
    return solid;
}

bool Block::isAir() const {
    return id == BLOCK_AIR;
}

void Blocks::initBlocks() {
    air = std::make_unique<Block>(BLOCK_AIR, false);
    dirt = std::make_unique<Block>(BLOCK_DIRT, true);
}
