#pragma once

#include <glm/glm.hpp>
#include <cstdint>
#include <memory>
#include <map>
#include <thread>

#include "world/chunk.h"
#include "world/generator.h"
#include "world/loading_thread.h"
#include "render/view/camera.h"
#include "util/runnable_queue.h"

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
    ~World();
    std::shared_ptr<Chunk> getChunkAt(const BlockPos &pos) const;
    std::shared_ptr<Chunk> getChunk(ChunkPos x, ChunkPos z) const;
    Chunks &getAndLockChunks();
    Chunks getChunksCopy() const;
    void lockChunks();
    void releaseChunks();
    BlockRef getBlock(const BlockPos &pos) const ;
    void setBlock(BlockRef block, const BlockPos &pos);
    void initWorld();

    // triggers the block update function and updates its render chunk
    void updateBlock(const BlockPos &pos);
    void breakBlock(const BlockPos &pos);
    RayResult trace(const glm::vec3 &pos, const glm::vec3 &dir, float len);
    RayResult trace(const Camera &cam, float len);

    bool shouldShutDown();
    void quit();

    // not thread safe
    void loadChunk(ChunkCoord pos);
    // not thread safe
    void unloadChunk(ChunkCoord pos);
    bool isChunkLoaded(ChunkCoord pos);

private:
    bool shutDown;

    Chunks chunks;
    Generator generator;

    std::mutex chunkLock;
    WorldLoadingThread chunkLoader;
    std::thread chunkThread;

    void rebuildAdjacentChunks(ChunkCoord pos);
};
