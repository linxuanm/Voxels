#include "chunk.h"

#include <iostream>

#include "game/voxels.h"
#include "world/blocks.h"

Chunk::Chunk(World &inWorld, ChunkPos inX, ChunkPos inZ)
: blocks{}, world(inWorld), x(inX), z(inZ) {
    for (int i = 0; i < CHUNK_HEIGHT >> 4; i++) {
        renderChunks[i] = RenderChunk{this, x, i, z};
    }
}

void Chunk::renderChunk() {
    for (auto &i: renderChunks) {
        i.tryInitGL();
        i.bufferChunk();
    }
}

void Chunk::rebuildChunkBuffer() {
    for (auto &i: renderChunks) {
        i.refresh();
    }
}

BlockRef Chunk::getBlockRel(const BlockPos &pos) {
    int idx = pos.y() << 8 | pos.x() << 4 | pos.z();
    if (idx < 0 || idx >= CHUNK_HEIGHT * 16 * 16) {
        return Blocks::air.get();
    }

    return blocks[pos.y() << 8 | pos.x() << 4 | pos.z()];
}

World &Chunk::getWorld() {
    return world;
}

void Chunk::updateRenderChunk(ChunkPos pos) {
    renderChunks[pos].refresh();
}

void Chunk::setBlockRel(BlockRef block, const BlockPos &pos) {
    int idx = pos.y() << 8 | pos.x() << 4 | pos.z();
    if (idx < 0 || idx >= CHUNK_HEIGHT * 16 * 16) return;

    blocks[idx] = block;
}

void Chunk::clearGL() {
    for (auto &i: renderChunks) {
        i.setDead();
    }
}
