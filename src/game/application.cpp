#include "application.h"

#include <iostream>

#include "util/config.h"
#include "util/log.h"
#include "util/specs.h"

Application::Application(): window(nullptr) {

}

Application &Application::get() {
    static Application app;

    return app;
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

}
