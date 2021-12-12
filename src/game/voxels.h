#pragma once

#include "render/world/world_renderer.h"

class Voxels {

public:
    static Voxels &get();
    void init();
    void drawFrame(float deltaTime);
    Camera &camera();

private:
    Voxels();
    WorldRenderer renderer;
};
