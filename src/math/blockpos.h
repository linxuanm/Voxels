#pragma once

#include "gl.h"
#include "render/world/blockface.h"

class BlockPos {

public:
    BlockPos(int xComp, int yComp, int zComp);
    BlockPos add(int x, int y, int z) const;
    BlockPos operator+(const BlockPos &other) const;
    BlockPos sub(int x, int y, int z) const;
    BlockPos operator-(const BlockPos &other) const;
    BlockPos operator*(float scalar) const;
    BlockPos operator+(GLfloat offset[3]) const;
    BlockPos offset(BlockFace::Facing face) const;
    int toChunkPos() const;
    int x() const;
    int y() const;
    int z() const;

private:
    int xComp, yComp, zComp;
};
