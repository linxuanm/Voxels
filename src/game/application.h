#pragma once

#include <glm/glm.hpp>

#include "gl.h"

namespace Application {

    extern GLFWwindow *window;
    extern float aspectRatio;
    extern glm::mat4 orthoViewMat;

    bool launch();
    void loop();
    void windowSize(int &width, int &height);
};
