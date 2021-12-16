#pragma once

#include <glm/glm.hpp>

#include "math/blockpos.h"

class Camera {

public:
    Camera();

    glm::mat4 getViewProjMat();
    glm::mat4 getViewMat();
    glm::mat4 getProjMat();
    float getYaw();
    void translate(float x, float y, float z);
    void rotate(float pitch, float yaw);
    BlockPos getCurrPos();

private:
    float x, y, z;
    float yaw, pitch;
};
