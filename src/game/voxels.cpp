#include "voxels.h"

#include "player/controller.h"
#include "util/input.h"

Voxels::Voxels()
: mouseOver({false, {0, 0, 0}}) {}

Voxels &Voxels::get() {
    static Voxels game;

    return game;
}

void Voxels::init() {
    renderer.init();

    world.initWorld();
}

RayResult& Voxels::getMouseOver() {
    return mouseOver;
}

void Voxels::drawFrame(float deltaTime) {
    Controller::updateMovement(renderer.camera(), deltaTime);

    mouseOver = world.trace(renderer.camera(), 5);

    renderer.drawWorld(world, deltaTime);
}

Camera &Voxels::camera() {
    return renderer.camera();
}

World& Voxels::getWorld() {
    return world;
}
