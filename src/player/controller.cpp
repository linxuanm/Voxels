#include "controller.h"

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtx/euler_angles.hpp>

#include "util/config.h"
#include "util/input.h"

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

    cam.translate(
        move[0] * Config::speed * deltaTime,
        move[1] * Config::speed * deltaTime,
        move[2] * Config::speed * deltaTime
    );
}
