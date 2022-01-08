#pragma once

#include <memory>

// should not be used other than internally
#define BLOCK_AIR 0
#define BLOCK_STONE 1
#define BLOCK_DIRT 2
#define BLOCK_GRASS 3
#define BLOCK_LOG 4
#define BLOCK_WATER 5

class Block {

public:
    Block(int inId, bool inSolid);
    bool isAir() const;
    bool isSolid() const;

private:
    int id;
    bool solid;
    //std::unique_ptr<IModel> blockModel;
};

typedef std::unique_ptr<Block> BlockDef;
typedef Block * BlockRef;

namespace Blocks {
    void initBlocks();

    extern BlockDef air;
    extern BlockDef dirt;
};
