#pragma once

#include <memory>

#include "render/model/model.h"

// Constants should not be used other than internally here.
#define BLOCK_AIR 0
#define BLOCK_STONE 1
#define BLOCK_DIRT 2
#define BLOCK_GRASS 3
#define BLOCK_LOG 4
#define BLOCK_WATER 5

class Block {

public:
    Block(int inId, bool inSolid, std::unique_ptr<IModel> inModel);
    bool isAir() const;
    bool isSolid() const;
    IModel *getModel() const;

private:
    int id;
    bool solid;
    std::unique_ptr<IModel> blockModel;
};

typedef std::unique_ptr<Block> BlockDef;
typedef Block * BlockRef;

namespace Blocks {
    void initBlocks();

    extern BlockDef air;
    extern BlockDef dirt;
    extern BlockDef stone;
    extern BlockDef grass;
};
