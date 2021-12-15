#pragma once

#include <cstdint>
#include <memory>

#include "render/view/buffer_builder.h"
#include "render/world/render_chunk.h"
#include "util/specs.h"

typedef int32_t ChunkPos;

class Chunk {

public:
    int blocks[CHUNK_HEIGHT * 16 * 16];

    Chunk(ChunkPos inX, ChunkPos inZ);
    void renderChunk();

private:
    int x, z;
    std::unique_ptr<RenderChunk> renderChunks[CHUNK_HEIGHT >> 4];
};
