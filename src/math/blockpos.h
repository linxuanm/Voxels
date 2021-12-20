#pragma once

#include <glm/glm.hpp>

#include "gl.h"
#include "render/world/blockface.h"

class BlockPos {

public:
    explicit BlockPos(glm::vec3 pos);
    BlockPos(int xComp, int yComp, int zComp);
    BlockPos(float xComp, float yComp, float zComp);
    BlockPos add(int x, int y, int z) const;
    BlockPos operator+(const BlockPos &other) const;
    BlockPos sub(int x, int y, int z) const;
    BlockPos operator-(const BlockPos &other) const;
    BlockPos operator*(float scalar) const;
    BlockPos operator+(GLfloat offset[3]) const;
    bool operator==(const BlockPos &pos) const;
    bool operator!=(const BlockPos &pos) const;
    BlockPos offset(BlockFace::Facing face) const;
    int toChunkPos() const;
    int x() const;
    int y() const;
    int z() const;

private:
    int xComp, yComp, zComp;
};
