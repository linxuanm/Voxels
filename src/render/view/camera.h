#pragma once

#include <glm/glm.hpp>

class Camera {

public:
    Camera();

    glm::mat4 getViewProjMat();
    void translate(float x, float y, float z);
    void rotate(float pitch, float yaw);

private:
    float x, y, z;
    float yaw, pitch;
};
