#pragma once

#include <queue>
#include <set>

#include "world/chunk.h"

class World;

enum ChunkActionType {
    ChunkLoadAction, ChunkUnloadAction
};

struct ChunkUpdate {
    ChunkUpdate(
        const ChunkCoord &pos,
        const ChunkActionType &action
    );

    ChunkCoord pos;
    ChunkActionType action;
};

class WorldLoadingThread {

public:
    explicit WorldLoadingThread(World &inWorld);
    void execute();

private:
    World &world;
    std::queue<ChunkUpdate> updateQueue;
    std::set<std::pair<ChunkPos, ChunkPos>> queued;

    bool cycle(); // returns true if world ends
    void runQueue();
};
