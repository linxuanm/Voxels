#pragma once

#include "gl.h"

namespace Input {
    extern bool mouseDown[];
    extern bool keysDown[];
    extern float lastMouseX;
    extern float lastMouseY;
    extern bool hideMouse;

    void keyCallback(GLFWwindow *win, int key, int scan, int act, int mod);
    void clickCallback(GLFWwindow *win, int key, int act, int mod);
    void mouseCallback(GLFWwindow *win, double x, double y);
    bool isKeyDown(int keyId);
    bool isMouseDown(int keyId);
    void fireKeyPress(int keyId);
};
