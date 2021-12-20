#include "controller.h"

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtx/euler_angles.hpp>

#include "util/config.h"
#include "util/input.h"
#include "game/voxels.h"

float Controller::mouseCooldown = 0;

void Controller::updateMovement(Camera &cam, float deltaTime) {
    glm::vec4 move{0, 0, 0, 0};

    if (Input::isKeyDown(GLFW_KEY_W)) move[2] -= 1;
    if (Input::isKeyDown(GLFW_KEY_S)) move[2] += 1;
    if (Input::isKeyDown(GLFW_KEY_A)) move[0] -= 1;
    if (Input::isKeyDown(GLFW_KEY_D)) move[0] += 1;
    if (Input::isKeyDown(GLFW_KEY_SPACE)) move[1] += 1;
    if (Input::isKeyDown(GLFW_KEY_LEFT_SHIFT)) move[1] -= 1;

    float yaw = cam.getYaw();
    glm::mat4 rotMat = glm::eulerAngleY(glm::radians(yaw));

    move = rotMat * move;
    move *= Config::speed * deltaTime;

    cam.translate(move.x, move.y, move.z);
}

void Controller::updateMouseAction(float deltaTime) {
    mouseCooldown -= deltaTime;

    if (mouseCooldown < 0) {
        if (Input::isMouseDown(GLFW_MOUSE_BUTTON_LEFT)) {
            if (Voxels::get().playerAttack()) {
                mouseCooldown = Config::actionCooldown;
            }
        } else if (Input::isMouseDown(GLFW_MOUSE_BUTTON_RIGHT)) {
            if (Voxels::get().playerPlace()) {
                mouseCooldown = Config::actionCooldown;
            }
        }
    }
}
