#include "input.h"

#include <iostream>

#include "game/application.h"

bool Input::keysDown[512];
bool Input::showMouse = true;

void Input::keyCallback(GLFWwindow *win, int key, int scan, int act, int mod) {

    // sanity check?
    if (key >= 512) {
        std::cout << "Invalid keycode: " << key << std::endl;
    }

    if (act == GLFW_PRESS) {
        keysDown[key] = true;

        Application::handleKeyPress(key);
    }
    else if (act == GLFW_RELEASE) keysDown[key] = false;
}

bool Input::isKeyDown(int keyId) {
    return keysDown[keyId];
}
