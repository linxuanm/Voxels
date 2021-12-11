#include "camera.h"

#include <glm/gtc/matrix_transform.hpp>

#include "game/application.h"
#include "util/config.h"

Camera::Camera(): z(1) {};

glm::mat4 Camera::getViewProjMat() {
    glm::mat4 proj = glm::perspective(
        Config::fov, Application::aspectRatio, 0.01f, 100.0f
    );

    glm::vec3 front{
        -cos(pitch) * sin(yaw),
        sin(pitch),
        -cos(pitch) * cos(yaw)
    };

    glm::vec3 eye{x, y, z};
    glm::mat4 view = glm::lookAt(eye, eye + front, {0, 1, 0});

    return proj * view;
}

void Camera::translate(float x, float y, float z) {
    this->x += x;
    this->y += y;
    this->z += z;
}

void Camera::rotate(float yaw, float pitch) {
    this->yaw += yaw;
    this->pitch += pitch;
}
