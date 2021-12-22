#pragma once

#include "render/view/camera.h"
#include "world/world.h"

class WorldRenderer {

public:
    WorldRenderer();
    ~WorldRenderer();

    void init();
    void drawWorld(World &world, float deltaTime);
    Camera &camera();

private:
    Camera cam;
    GLuint boxVao; // for any simple, generic box geometry
    GLuint boxVbo;
    GLuint hudVao;
    GLuint hudVbo;

    void drawSkybox();
    void drawOverlay();
    void drawWorldOverlay();
};
