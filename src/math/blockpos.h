#pragma once

#include "gl.h"

class BlockPos {

public:
    BlockPos(int xComp, int yComp, int zComp);
    BlockPos add(int x, int y, int z);
    BlockPos operator+(const BlockPos &other);
    BlockPos sub(int x, int y, int z);
    BlockPos operator-(const BlockPos &other);
    BlockPos operator*(float scalar);
    BlockPos operator+(GLfloat offset[3]) const;
    int toChunkPos();
    int x() const;
    int y() const;
    int z() const;

private:
    int xComp, yComp, zComp;
};
