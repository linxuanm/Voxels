#pragma once

#include "render/view/camera.h"

class WorldRenderer {

public:
    void init();
    void drawWorld(float deltaTime);
    Camera &camera();

private:
    Camera cam;
};
