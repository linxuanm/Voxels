#pragma once

#include <glm/glm.hpp>

#include "math/blockpos.h"

class Camera {

public:
    Camera();

    glm::mat4 getViewProjMat() const;
    glm::mat4 getViewMat() const;
    glm::mat4 getProjMat() const;
    float getYaw() const;
    void translate(float x, float y, float z);
    void rotate(float pitch, float yaw);
    BlockPos getCurrBlock() const;
    glm::vec3 getCurrPos() const;
    glm::vec3 getForward() const;

private:
    float x, y, z;
    float yaw, pitch;
};
