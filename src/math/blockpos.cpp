#include "blockpos.h"

#include <cmath>

BlockPos::BlockPos(int x, int y, int z): xComp(x), yComp(y), zComp(z) {}

BlockPos::BlockPos(float x, float y, float z)
: xComp(static_cast<int>(floor(x)))
, yComp(static_cast<int>(floor(y)))
, zComp(static_cast<int>(floor(z))) {}

BlockPos::BlockPos(glm::vec3 pos)
: BlockPos(glm::floor(pos.x), glm::floor(pos.y), glm::floor(pos.z)) {}

BlockPos BlockPos::add(int x, int y, int z) const {
    return {xComp + x, yComp + y, zComp + z};
}

BlockPos BlockPos::operator+(const BlockPos &other) const {
    return add(other.xComp, other.yComp, other.zComp);
}

BlockPos BlockPos::sub(int x, int y, int z) const {
    return {xComp - x, yComp - y, zComp - z};
}

BlockPos BlockPos::operator-(const BlockPos &other) const {
    return sub(other.xComp, other.yComp, other.zComp);
}

BlockPos BlockPos::operator*(float scalar) const {
    return {
        (int) (scalar * xComp),
        (int) (scalar * yComp),
        (int) (scalar * zComp)
    };
}

BlockPos BlockPos::operator+(GLfloat offset[3]) const {
    return {
        xComp + (int) offset[0],
        yComp + (int) offset[1],
        zComp + (int) offset[2]
    };
}

bool BlockPos::operator==(const BlockPos &pos) const {
    return pos.xComp == xComp && pos.yComp == yComp && pos.zComp == zComp;
}

bool BlockPos::operator!=(const BlockPos &pos) const {
    return !operator==(pos);
}

BlockPos BlockPos::offset(BlockFace::Facing face) const {
    switch (face) {
        case BlockFace::UP: return add(0, 1, 0);
        case BlockFace::DOWN: return add(0, -1, 0);
        case BlockFace::WEST: return add(-1, 0, 0);
        case BlockFace::EAST: return add(1, 0, 0);
        case BlockFace::NORTH: return add(0, 0, -1);
        case BlockFace::SOUTH: return add(0, 0, 1);
    }

    return *this;
}

int BlockPos::toChunkPos() const {
    int x = xComp & 15;
    int y = yComp;
    int z = zComp & 15;

    return y << 8 | x << 4 | z;
}

int BlockPos::x() const {
    return xComp;
}

int BlockPos::y() const {
    return yComp;
}

int BlockPos::z() const {
    return zComp;
}
