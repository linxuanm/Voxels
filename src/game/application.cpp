#include "application.h"

#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include "util/input.h"
#include "game/voxels.h"
#include "util/config.h"
#include "util/log.h"
#include "util/specs.h"

GLFWwindow *Application::window = nullptr;
float Application::aspectRatio = 1.0f;
glm::mat4 Application::orthoViewMat;

#include <iostream>
static void resize(GLFWwindow *window, int width, int height) {
    Application::aspectRatio = (float) width / height;
    glViewport(0, 0, width, height);

    float hudX = width;
    float hudY = height;

    float centerX = (GLfloat) hudX / 2;
    float centerY = (GLfloat) hudY / 2;

    glm::mat4 ortho = glm::ortho(0.0f, hudX, hudY, 0.0f);
    glm::mat4 view = glm::translate(glm::vec3{centerX, centerY, 0.0f});
    Application::orthoViewMat = ortho * view;
}

static void viewportSetup() {
    int width, height;
    glfwGetFramebufferSize(Application::window, &width, &height);

    resize(Application::window, width, height);
}

void Application::windowSize(int &width, int &height) {
    glfwGetFramebufferSize(Application::window, &width, &height);
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
    glfwSetMouseButtonCallback(window, Input::clickCallback);

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
