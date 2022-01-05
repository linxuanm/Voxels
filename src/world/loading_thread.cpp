#include "loading_thread.h"

#include <set>
#include <chrono>
#include <thread>

#include "util/config.h"
#include "world/world.h"
#include "game/voxels.h"

static std::pair<ChunkPos, ChunkPos> getPlayerChunk() {
    Voxels &vox = Voxels::get();
    glm::vec3 playerPos = glm::floor(vox.camera().getCurrPos());
    return {
        static_cast<ChunkPos>(playerPos.x) >> 4,
        static_cast<ChunkPos>(playerPos.z) >> 4
    };
}

static float dist(
    std::pair<ChunkPos, ChunkPos> a, std::pair<ChunkPos, ChunkPos> b
    ) {
    ChunkPos dx = a.first - b.first;
    ChunkPos dy = a.second - b.second;

    return (float) sqrt(dx * dx + dy * dy);
}

ChunkUpdate::ChunkUpdate(
    const std::pair<ChunkPos, ChunkPos> &inPos,
    const ChunkActionType &inAct
): pos(inPos), action(inAct) {}

WorldLoadingThread::WorldLoadingThread(World &inWorld)
: world(inWorld) {}

void WorldLoadingThread::execute() {
    while (!cycle()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}

void WorldLoadingThread::runQueue() {
    if (!updateQueue.empty()) {
        world.lockChunks();

        for (int i = 0; i < Config::maxChunkLoadPerSec; i++) {
            if (updateQueue.empty()) break;

            auto [pos, tag] = updateQueue.front();
            updateQueue.pop();
            queued.erase(pos);

            if (tag == ChunkLoadAction) {
                world.loadChunk(pos);
            } else {
                /*
                 * Reobtaining the player pos is necessary as in the
                 * future the queue thread might not run in sync with
                 * the cycle function.
                 */
                auto currChunk = getPlayerChunk();

                if (dist(currChunk, pos) > Config::renderDist) {
                    world.unloadChunk(pos);
                }
            }
        }

        world.releaseChunks();
    }
}

#include <iostream>
bool WorldLoadingThread::cycle() {
    auto currChunk = getPlayerChunk();

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

    Chunks chunks = world.getChunksCopy();
    for (auto &loaded: chunks) {
        auto place = inRange.find(loaded.first);
        if (place == inRange.end()) {
            if (!queued.count(loaded.first)) {
                updateQueue.emplace(
                    loaded.first, ChunkUnloadAction
                );
                queued.insert(loaded.first);
            }
        } else {
            inRange.erase(place);
        }
    }

    for (auto &toLoad: inRange) {
        if (!world.isChunkLoaded(toLoad) && !queued.count(toLoad)) {
            updateQueue.emplace(toLoad, ChunkLoadAction);
            queued.insert(toLoad);
        }
    }

    runQueue();

    return world.shouldShutDown();
}
