#include "blocks.h"

#include "render/texture.h"

BlockDef Blocks::air;
BlockDef Blocks::dirt;
BlockDef Blocks::stone;
BlockDef Blocks::grass;

Block::Block(int inId, bool inSolid, std::unique_ptr<IModel> inModel)
: id(inId), solid(inSolid), blockModel(std::move(inModel)) {}

bool Block::isSolid() const {
    return solid;
}

bool Block::isAir() const {
    return id == BLOCK_AIR;
}

IModel *Block::getModel() const {
    return blockModel.get();
}

void Blocks::initBlocks() {
    air = std::make_unique<Block>(
        BLOCK_AIR, false,
        nullptr
    );
    dirt = std::make_unique<Block>(
        BLOCK_DIRT, true,
        std::make_unique<SixFaceModel>(BLOCK_DIRT_UV)
    );
    stone = std::make_unique<Block>(
        BLOCK_STONE, true,
        std::make_unique<SixFaceModel>(BLOCK_STONE_UV)
    );
    grass = std::make_unique<Block>(
        BLOCK_GRASS, true,
        std::make_unique<FourFaceModel>(
            BLOCK_GRASS_TOP_UV, BLOCK_GRASS_SIDE_UV, BLOCK_DIRT_UV
        )
    );
}
