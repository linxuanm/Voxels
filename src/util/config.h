#pragma once

#include "world/chunk.h"

namespace Config {

    void load();

    extern float fov;
    extern float speed;
    extern float mouseSen;
    extern float reachDistance;
    extern float actionCooldown;
    extern float crosshairSize;
    extern ChunkPos renderDist;
};
