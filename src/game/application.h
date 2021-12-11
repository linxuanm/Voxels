#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace Application {

    extern GLFWwindow *window;
    extern float aspectRatio;

    void windowSize(int *width, int *height);

    bool launch();
    void loop();
};
