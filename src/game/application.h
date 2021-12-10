#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Application {

public:
    static Application &get();

    bool launch();
    void loop();

private:
    GLFWwindow *window;

    Application();
};
