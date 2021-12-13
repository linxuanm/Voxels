#pragma once

#include "render/view/camera.h"
#include "world/world.h"

class WorldRenderer {

public:
    void init();
    void drawWorld(World world, float deltaTime);
    Camera &camera();

private:
    Camera cam;
};
