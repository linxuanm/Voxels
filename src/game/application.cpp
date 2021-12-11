#include "application.h"

#include <iostream>

#include "util/config.h"
#include "util/log.h"
#include "util/specs.h"

GLFWwindow *Application::window = nullptr;
float Application::aspectRatio = 1.0f;

static void resize(GLFWwindow *window, int width, int height) {
    Application::aspectRatio = (float) width / height;
}

void Application::windowSize(int *width, int *height) {
    glfwGetWindowSize(window, width, height);
}

bool Application::launch() {
    Config::load();

    if (!glfwInit()) {
        std::cout << "GLFW INITIALIZATION FAILED" << std::endl;
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    window = glfwCreateWindow(
        WIN_WIDTH, WIN_HEIGHT, WIN_TITLE, nullptr, nullptr
    );

    if (!window) {
        glfwTerminate();
        std::cout << "WINDOW CREATION FAILED" << std::endl;

        return false;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, resize);
    // glfwSetKeyCallback(window, Input::keyCallback);

    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK) {
        glfwTerminate();
        std::cout << "GLEW INITIALIZATION FAILED" << std::endl;

        return false;
    }

    Log::printVersions();

    return true;
}

void Application::loop() {
    glfwSwapBuffers(window);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();

        Log::logGLError();

        #ifdef __APPLE__ // update window on Mac OS
        static bool macUpdate = false;

        if(!macUpdate) {
            int x, y;
            glfwGetWindowPos(window, &x, &y);
            glfwSetWindowPos(window, x + 1, y);
            macUpdate = true;
        }
        #endif
    }
}
