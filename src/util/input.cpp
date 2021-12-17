#include "input.h"

#include <iostream>

#include "render/view/camera.h"
#include "game/application.h"
#include "game/voxels.h"
#include "util/config.h"

bool Input::keysDown[512];
float Input::lastMouseX;
float Input::lastMouseY;
bool Input::hideMouse = true;

void Input::keyCallback(GLFWwindow *win, int key, int scan, int act, int mod) {

    // sanity check?
    if (key >= 512) {
        std::cout << "Invalid keycode: " << key << std::endl;
    }

    if (act == GLFW_PRESS) {
        keysDown[key] = true;

        Input::fireKeyPress(key);
    }
    else if (act == GLFW_RELEASE) keysDown[key] = false;
}

void Input::mouseCallback(GLFWwindow *win, double x, double y) {
    float dx = (lastMouseX - (float) x) * Config::mouseSen;
    float dy = (lastMouseY - (float) y) * Config::mouseSen;

    lastMouseX = (float) x;
    lastMouseY = (float) y;

    Camera &cam = Voxels::get().camera();
    cam.rotate(dx, dy);
}

bool Input::isKeyDown(int keyId) {
    return keysDown[keyId];
}

void Input::fireKeyPress(int keyId) {
    if (keyId == GLFW_KEY_E) {
        hideMouse = !hideMouse;
        glfwSetInputMode(
            Application::window, GLFW_CURSOR,
            hideMouse ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL
        );
    }
    if (keyId == GLFW_KEY_R) {
        Voxels::get().getWorld().breakBlock(Voxels::get().camera().getCurrBlock());
    }
}
