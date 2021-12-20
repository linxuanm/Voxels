#pragma once

#include "render/view/camera.h"

namespace Controller {

    extern float mouseCooldown;

    void updateMovement(Camera &cam, float deltaTime);
    void updateMouseAction(float deltaTime);
};
