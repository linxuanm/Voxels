#include "camera.h"

#include <glm/gtc/matrix_transform.hpp>
#include <cmath>

#include "game/application.h"
#include "util/config.h"

Camera::Camera(): x(0.5), y(0.5), z(0.5) {}

glm::mat4 Camera::getViewProjMat() {
    return getProjMat() * getViewMat();
}

glm::mat4 Camera::getViewMat() {
    float radPitch = glm::radians(pitch);
    float radYaw = glm::radians(yaw);

    glm::vec3 front{
        -cos(radPitch) * sin(radYaw),
        sin(radPitch),
        -cos(radPitch) * cos(radYaw)
    };

    glm::vec3 eye{x, y, z};
    return glm::lookAt(eye, eye + front, {0, 1, 0});
}

glm::mat4 Camera::getProjMat() {
    return glm::perspective(
        Config::fov, Application::aspectRatio, 0.01f, 100.0f
    );
}

float Camera::getYaw() {
    return yaw;
}

void Camera::translate(float x, float y, float z) {
    this->x += x;
    this->y += y;
    this->z += z;
}

void Camera::rotate(float dYaw, float dPitch) {
    yaw += dYaw;
    pitch = glm::clamp(pitch + dPitch, -89.9f, 89.9f);
}

BlockPos Camera::getCurrPos() {
    return {
        static_cast<int>(floor(x)),
        static_cast<int>(floor(y)),
        static_cast<int>(floor(z))
    };
}
