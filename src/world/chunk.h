#pragma once

#include <cstdint>
#include <memory>

#include "render/view/buffer_builder.h"
#include "render/world/render_chunk.h"
#include "util/specs.h"

typedef int32_t ChunkPos;

class World;

class Chunk {

public:
    int blocks[CHUNK_HEIGHT * 16 * 16];

    Chunk(World &inWorld, ChunkPos inX, ChunkPos inZ);
    void renderChunk();
    void rebuildChunkBuffer();
    World &getWorld();
    int getBlockRel(const BlockPos &pos);
    void updateRenderChunk(ChunkPos pos);

    // sets block without triggering any updates, etc
    void setBlockRel(int block, const BlockPos &pos);

    // called just before freeing this chunk to clean up
    void clearGL();

private:
    int x, z;
    World &world;
    RenderChunk renderChunks[CHUNK_HEIGHT >> 4];
};
