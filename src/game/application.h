#pragma once

#include <GL/glew.h>

#include "gl.h"

namespace Application {

    extern GLFWwindow *window;
    extern float aspectRatio;
    extern bool hideMouse;

    void windowSize(int *width, int *height);
    void handleKeyPress(int key);

    bool launch();
    void loop();
};
