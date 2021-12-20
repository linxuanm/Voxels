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

struct RayResult {
    bool hit;
    BlockPos pos;
    BlockFace::Facing hitFace;
};

class World {

public:
    World();
    std::shared_ptr<Chunk> getChunkAt(const BlockPos &pos);
    std::shared_ptr<Chunk> getChunk(ChunkPos x, ChunkPos z);
    Chunks &getChunks();
    int getBlock(const BlockPos &pos);
    void setBlock(int block, const BlockPos &pos);
    void initWorld();

    // triggers the block update function and updates its render chunk
    void updateBlock(const BlockPos &pos);
    void breakBlock(const BlockPos &pos);
    RayResult trace(const glm::vec3 &pos, const glm::vec3 &dir, float len);
    RayResult trace(const Camera &cam, float len);

private:
    Chunks chunks;
    Generator generator;
};
