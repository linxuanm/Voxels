#pragma once

#include <glm/glm.hpp>
#include <cstdint>
#include <memory>
#include <map>

#include "world/chunk.h"
#include "world/generator.h"
#include "render/view/camera.h"

// shared_ptr for potentially delayed dealloc during world saving
typedef std::map<std::pair<ChunkPos, ChunkPos>, std::shared_ptr<Chunk>> Chunks;

struct RayCastResult {
    bool hit;
    BlockPos pos;

    //RayCastResult(bool inHit, const BlockPos &inPos);
};

class World {

public:
    World();
    std::shared_ptr<Chunk> getChunkAt(const BlockPos &pos);
    std::shared_ptr<Chunk> getChunk(ChunkPos x, ChunkPos z);
    Chunks &getChunks();
    int getBlock(const BlockPos &pos);
    void initWorld();

    // triggers the block update function and updates its render chunk
    void updateBlock(const BlockPos &pos);
    void breakBlock(const BlockPos &pos);
    RayCastResult traceBlock(const glm::vec3 &start, const glm::vec3 &end);
    RayCastResult traceBlock(const Camera &cam, float length);

private:
    Chunks chunks;
    Generator generator;
};
