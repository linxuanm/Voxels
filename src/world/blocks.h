#pragma once

#include <memory>

#define BLOCK_AIR 0
#define BLOCK_STONE 1
#define BLOCK_DIRT 2
#define BLOCK_GRASS 3
#define BLOCK_LOG 4
#define BLOCK_WATER 5

class Block {

public:
    explicit Block(int inId);

private:
    int id;
    //std::unique_ptr<IModel> blockModel;
};

namespace Blocks {
    bool isSolid(int block);


};
