#include "voxels.h"

#include "player/controller.h"
#include "util/input.h"
#include "util/config.h"
#include "world/blocks.h"

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

RayResult &Voxels::getMouseOver() {
    return mouseOver;
}

void Voxels::drawFrame(float deltaTime) {
    taskQueue.runAll();

    Controller::updateMouseAction(deltaTime);
    Controller::updateMovement(renderer.camera(), deltaTime);

    mouseOver = world.trace(renderer.camera(), Config::reachDistance);

    renderer.drawWorld(world, deltaTime);
}

Camera &Voxels::camera() {
    return renderer.camera();
}

World& Voxels::getWorld() {
    return world;
}

bool Voxels::playerAttack() {
    if (mouseOver.hit) {
        world.breakBlock(mouseOver.pos);
        return true;
    }

    return false;
}

bool Voxels::playerPlace() {
    if (mouseOver.hit && mouseOver.pos != camera().getCurrBlock()) {
        world.setBlock(BLOCK_DIRT, mouseOver.pos.offset(mouseOver.hitFace));
        return true;
    }

    return false;
}

void Voxels::end() {
    world.quit();
}

void Voxels::scheduleTask(std::function<void()> func) {
    taskQueue.push_back(func);
}
