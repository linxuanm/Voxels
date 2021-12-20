#pragma once

#include "render/view/camera.h"
#include "world/world.h"

class WorldRenderer {

public:
    WorldRenderer();
    ~WorldRenderer();

    void init();
    void drawWorld(World world, float deltaTime);
    Camera &camera();

private:
    Camera cam;
    GLuint skyVao;
    GLuint skyVbo;

    void drawSkybox();
    void drawOverlay();
};
