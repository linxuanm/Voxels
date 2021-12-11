#include "controller.h"

#include <iostream>
#include <util/config.h>

#include "util/input.h"

void Controller::updateMovement(Camera &cam, float deltaTime) {
    int x = 0, y = 0, z = 0;

    if (Input::isKeyDown(GLFW_KEY_W)) z -= 1;
    if (Input::isKeyDown(GLFW_KEY_S)) z += 1;
    if (Input::isKeyDown(GLFW_KEY_A)) x -= 1;
    if (Input::isKeyDown(GLFW_KEY_D)) x += 1;
    if (Input::isKeyDown(GLFW_KEY_SPACE)) y += 1;
    if (Input::isKeyDown(GLFW_KEY_LEFT_SHIFT)) y -= 1;

    cam.translate(
        x * Config::speed * deltaTime,
        y * Config::speed * deltaTime,
        z * Config::speed * deltaTime
    );
}
