#pragma once

#include <cstdint>
#include <memory>
#include <unordered_map>

#include "world/chunk.h"

// shared_ptr for potentially delayed dealloc during world saving
typedef std::unordered_map<int64_t, std::shared_ptr<Chunk>> ChunkMap;

class World {

public:
    World();
    std::shared_ptr<Chunk> getBlockChunk(int x, int z);
    std::shared_ptr<Chunk> getChunk(ChunkPos x, ChunkPos z);

private:
    ChunkMap chunks;
};