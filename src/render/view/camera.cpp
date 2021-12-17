#include "camera.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <cmath>

#include "game/application.h"
#include "util/config.h"

Camera::Camera(): x(0.5), y(20.5), z(0.5) {}

glm::mat4 Camera::getViewProjMat() const {
    return getProjMat() * getViewMat();
}

glm::mat4 Camera::getViewMat() const {
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

glm::mat4 Camera::getProjMat() const {
    return glm::perspective(
        Config::fov, Application::aspectRatio, 0.01f, 100.0f
    );
}

float Camera::getYaw() const {
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

BlockPos Camera::getCurrBlock() const {
    return {x, y, z};
}

glm::vec3 Camera::getCurrPos() const {
    return {x, y, z};
}

glm::vec3 Camera::getForward() const {
    float radYaw = glm::radians(yaw);
    float radPitch = glm::radians(pitch);
    return glm::normalize(glm::vec3{
        -glm::sin(radYaw) * glm::cos(radPitch),
        glm::sin(radPitch),
        glm::cos(radYaw) * glm::cos(radPitch)
    });
}
