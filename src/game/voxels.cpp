#include "voxels.h"

#include <GLFW/glfw3.h>

#include "player/controller.h"

Voxels::Voxels() = default;

Voxels &Voxels::get() {
    static Voxels game;

    return game;
}

void Voxels::init() {
    renderer.init();
}

void Voxels::drawFrame(float deltaTime) {
    Controller::updateMovement(renderer.camera(), deltaTime);
    renderer.drawWorld(deltaTime);
}
