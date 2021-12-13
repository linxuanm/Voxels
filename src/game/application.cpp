#include "application.h"

#include <iostream>

#include "util/input.h"
#include "game/voxels.h"
#include "util/config.h"
#include "util/log.h"
#include "util/specs.h"

GLFWwindow *Application::window = nullptr;
float Application::aspectRatio = 1.0f;

static void resize(GLFWwindow *window, int width, int height) {
    Application::aspectRatio = (float) width / height;
}

static void viewportSetup() {
    int width, height;
    glfwGetWindowSize(Application::window, &width, &height);

    resize(Application::window, width, height);
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
    glfwSetKeyCallback(window, Input::keyCallback);

    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK) {
        glfwTerminate();
        std::cout << "GLEW INITIALIZATION FAILED" << std::endl;

        return false;
    }

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    if (glfwRawMouseMotionSupported()) {
        glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
    }
    glfwSetCursorPosCallback(window, Input::mouseCallback);

    Log::printVersions();

    return true;
}

void Application::loop() {
    Voxels::get().init();
    viewportSetup();

    glfwSwapBuffers(window); // Mac OS

    auto deltaTime = (float) glfwGetTime();
    float lastFrame = deltaTime;

    while (!glfwWindowShouldClose(window)) {
        auto currTime = (float) glfwGetTime();
        deltaTime = currTime - lastFrame;
        lastFrame = currTime;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        Voxels::get().drawFrame(deltaTime);

        glfwSwapBuffers(window);
        glfwPollEvents();

        Log::logGLError();
    }
}
