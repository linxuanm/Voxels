#include "camera.h"

#include <glm/gtc/matrix_transform.hpp>

#include "game/application.h"
#include "util/config.h"

Camera::Camera(): z(1) {};

glm::mat4 Camera::getViewProjMat() {
    glm::mat4 proj = glm::perspective(
        Config::fov, Application::aspectRatio, 0.1f, 100.0f
    );

    glm::vec3 front{
        -cos(pitch) * sin(yaw),
        sin(pitch),
        -cos(pitch) * cos(yaw)
    };

    glm::mat4 view = glm::lookAt({x, y, z}, front, {0, 1, 0});
    return proj * view;
}

void Camera::rotate(float yaw, float pitch) {
    this->yaw += yaw;
    this->pitch += pitch;
}
