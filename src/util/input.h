#pragma once

#include <GL/glew.h>

#include "gl.h"

namespace Input {
    extern bool keysDown[];
    extern bool showMouse;

    void keyCallback(GLFWwindow *win, int key, int scan, int act, int mod);
    bool isKeyDown(int keyId);
};
