#pragma once

class BlockPos {

public:
    BlockPos(int xComp, int yComp, int zComp);
    BlockPos add(int x, int y, int z);
    BlockPos add(BlockPos other);
    BlockPos sub(int x, int y, int z);
    BlockPos sub(BlockPos other);
    BlockPos mul(float scalar);
    int toChunkPos();
    int x();
    int y();
    int z();

private:
    int xComp, yComp, zComp;
};
