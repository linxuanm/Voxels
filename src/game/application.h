#pragma once

#include "gl.h"

namespace Application {

    extern GLFWwindow *window;
    extern float aspectRatio;

    bool launch();
    void loop();
};
