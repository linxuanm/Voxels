#pragma once

#include <cstdint>
#include <memory>
#include <map>

#include "world/chunk.h"
#include "world/generator.h"

// shared_ptr for potentially delayed dealloc during world saving
typedef std::map<std::pair<ChunkPos, ChunkPos>, std::shared_ptr<Chunk>> Chunks;

class World {

public:
    World();
    std::shared_ptr<Chunk> getBlockChunk(int x, int z);
    std::shared_ptr<Chunk> getChunk(ChunkPos x, ChunkPos z);
    Chunks &getChunks();
    int getBlock(const BlockPos &pos);
    void initWorld();

private:
    Chunks chunks;
    Generator generator;
};
