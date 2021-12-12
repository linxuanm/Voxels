#pragma once

#include <GL/glew.h>

#include "gl.h"

namespace Application {

    extern GLFWwindow *window;
    extern float aspectRatio;

    bool launch();
    void loop();
};
