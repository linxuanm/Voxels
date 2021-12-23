#include "loading_thread.h"

#include <set>
#include <chrono>
#include <thread>

#include "util/config.h"
#include "world/world.h"
#include "game/voxels.h"

WorldLoadingThread::WorldLoadingThread(World &inWorld)
: world(inWorld) {}

void WorldLoadingThread::execute() {
    while (!cycle()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

bool WorldLoadingThread::cycle() {
    Voxels &vox = Voxels::get();
    glm::vec3 playerPos = glm::floor(vox.camera().getCurrPos());
    std::pair<ChunkPos, ChunkPos> currChunk{
        static_cast<ChunkPos>(playerPos.x) >> 4,
        static_cast<ChunkPos>(playerPos.z) >> 4
    };

    std::set<std::pair<ChunkPos, ChunkPos>> inRange;

    const ChunkPos radius = Config::renderDist;
    for (ChunkPos i = -radius; i <= radius; i++) {
        for (ChunkPos j = -radius; j <= radius; j++) {
            if (glm::sqrt((float) (i * i + j * j)) <= radius) {
                inRange.insert({
                    i + currChunk.first,
                    j + currChunk.second
                });
            }
        }
    }

    Chunks &chunks = world.getAndLockChunks();
    for (auto &loaded: chunks) {
        auto place = inRange.find(loaded.first);
        if (place == inRange.end()) {
            // TODO: use iterator for removing to prevent O(2 * log N)
            //world.unloadChunk(loaded.first);
        } else {
            inRange.erase(place);
        }
    }

    for (auto &toLoad: inRange) {
        world.loadChunk(toLoad);
    }

    world.releaseChunks();

    return world.shouldShutDown();
}
