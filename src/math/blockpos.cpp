#include "blockpos.h"

BlockPos::BlockPos(int x, int y, int z): xComp(x), yComp(y), zComp(z) {}

BlockPos BlockPos::add(int x, int y, int z) {
    return {xComp + x, yComp + y, zComp + z};
}

BlockPos BlockPos::add(BlockPos other) {
    return add(other.xComp, other.yComp, other.zComp);
}

BlockPos BlockPos::sub(int x, int y, int z) {
    return {xComp - x, yComp - y, zComp - z};
}

BlockPos BlockPos::sub(BlockPos other) {
    return sub(other.xComp, other.yComp, other.zComp);
}

BlockPos BlockPos::mul(float scalar) {
    return {
        (int) (scalar * xComp),
        (int) (scalar * yComp),
        (int) (scalar * zComp)
    };
}

BlockPos BlockPos::offset(GLfloat *offset) const {
    return {
        xComp + (int) offset[0],
        yComp + (int) offset[1],
        zComp + (int) offset[2]
    };
}

int BlockPos::toChunkPos() {
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
