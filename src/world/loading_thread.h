#pragma once

class World;

class WorldLoadingThread {

public:
    explicit WorldLoadingThread(World &inWorld);
    void execute();

private:
    World &world;
    void cycle();
};
