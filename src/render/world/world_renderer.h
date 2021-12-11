#pragma once

#include "render/view/camera.h"

class WorldRenderer {

public:
    void init();
    void drawWorld(float deltaTime);

private:
    Camera cam;
};
