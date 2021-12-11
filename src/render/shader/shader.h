#pragma once

#include <string>

#include "gl.h"

class Shader {

public:
    // different vert/frag combination is rare in Voxels' case
    Shader(std::string &vertPath, std::string &fragPath);
    ~Shader();

    void bind();
    GLint getUniformLocation(GLchar *name);

private:
    GLuint program;
};
