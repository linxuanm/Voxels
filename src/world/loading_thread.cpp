#include "loading_thread.h"

#include <map>

#include "world/world.h"
#include "game/voxels.h"

WorldLoadingThread::WorldLoadingThread(World &inWorld)
: world(inWorld) {}

void WorldLoadingThread::execute() {
    while (!cycle());
}

bool WorldLoadingThread::cycle() {
    Voxels &vox = Voxels::get();
    glm::vec3 playerPos = glm::floor(vox.camera().getCurrPos());
    std::pair<ChunkPos, ChunkPos> currChunk{
        static_cast<ChunkPos>(playerPos.x) >> 4,
        static_cast<ChunkPos>(playerPos.z) > 4
    };

    return world.shouldShutDown();
}
