#include "chunk.h"

Chunk::Chunk(ChunkPos inX, ChunkPos inZ)
: blocks{}, x(inX), z(inZ) {
    for (int i = 0; i < CHUNK_HEIGHT >> 4; i++) {
        renderChunks[i] = std::make_unique<RenderChunk>(x, i, z);
    }
}

void Chunk::renderChunk() {
    for (auto &i: renderChunks) {
        i->renderSection();
    }
}
