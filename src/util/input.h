#pragma once

#include "gl.h"

namespace Input {
    extern bool keysDown[];

    void keyCallback(GLFWwindow *win, int key, int scan, int act, int mod);
    bool isKeyDown(int keyId);
};
