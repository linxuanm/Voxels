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

int BlockPos::toChunkPos() {
    int x = xComp & 15;
    int y = yComp;
    int z = zComp & 15;

    return y << 8 | x << 4 | z;
}

int BlockPos::x() {
    return xComp;
}

int BlockPos::y() {
    return yComp;
}

int BlockPos::z() {
    return zComp;
}
