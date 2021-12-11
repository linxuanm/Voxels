#include "voxels.h"

Voxels::Voxels() = default;

Voxels &Voxels::get() {
    static Voxels game;

    return game;
}

void Voxels::init() {
    renderer.init();
}

void Voxels::drawFrame(float deltaTime) {
    renderer.drawWorld(deltaTime);
}
