#include "voxels.h"

#include "player/controller.h"
#include "util/input.h"

Voxels::Voxels() = default;

Voxels &Voxels::get() {
    static Voxels game;

    return game;
}

void Voxels::init() {
    renderer.init();

    world.initWorld();
}

void Voxels::drawFrame(float deltaTime) {
    Controller::updateMovement(renderer.camera(), deltaTime);
    renderer.drawWorld(world, deltaTime);
}

Camera &Voxels::camera() {
    return renderer.camera();
}

World& Voxels::getWorld() {
    return world;
}
