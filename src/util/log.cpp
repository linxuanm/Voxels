#include "log.h"

#include <iostream>

#include "gl.h"

void Log::printVersions() {
    std::cout << "Launching Voxels 0.1" << std::endl;

    std::cout << "OpenGL Version: " << glGetString(GL_VERSION);
    std::cout << std::endl;

    std::cout << "GLSL Versions: ";
    std::cout << glGetString(GL_SHADING_LANGUAGE_VERSION);
    std::cout << std::endl;

    std::cout << std::endl;
}

void Log::logGLError() {
    while (GLenum err = glGetError()) {
        std::cout << "OPENGL ERROR: " << err << std::endl;
    }
}
