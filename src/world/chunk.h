#pragma once

#include <cstdint>
#include <memory>

#include "world/blocks.h"
#include "render/view/buffer_builder.h"
#include "render/world/render_chunk.h"
#include "util/specs.h"

typedef std::pair<ChunkPos, ChunkPos> ChunkCoord;

class World;

class Chunk {

public:
    BlockRef blocks[CHUNK_HEIGHT * 16 * 16];

    Chunk(World &inWorld, ChunkPos inX, ChunkPos inZ);
    void renderChunk();
    void rebuildChunkBuffer();
    World &getWorld();
    BlockRef getBlockRel(const BlockPos &pos);
    void updateRenderChunk(ChunkPos pos);

    // sets block without triggering any updates, etc
    void setBlockRel(BlockRef block, const BlockPos &pos);

    // called just before freeing this chunk to clean up
    void clearGL();

private:
    int x, z;
    World &world;
    RenderChunk renderChunks[CHUNK_HEIGHT >> 4];
};
