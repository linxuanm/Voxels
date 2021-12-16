#include "chunk.h"

Chunk::Chunk(ChunkPos inX, ChunkPos inZ)
: blocks{}, x(inX), z(inZ) {
    for (int i = 0; i < CHUNK_HEIGHT >> 4; i++) {
        renderChunks[i] = std::make_unique<RenderChunk>(*this, x, i, z);
    }
}

void Chunk::renderChunk() {
    for (auto &i: renderChunks) {
        i->bufferChunk();
    }
}

int Chunk::getBlockRel(const BlockPos &pos) {
    return blocks[pos.y() << 8 | pos.x() << 4 | pos.z()];
}
