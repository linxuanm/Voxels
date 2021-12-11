#pragma once

#include <glm/glm.hpp>

class Camera {

public:
    Camera();

    glm::mat4 getViewProjMat();
    void rotate(float pitch, float yaw);

private:
    float x, y, z;
    float yaw, pitch;
};
