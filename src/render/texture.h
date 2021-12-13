#pragma once

#include <string>

#include "gl.h"

class Texture {

public:
    explicit Texture(std::string path);
    ~Texture();

    void bind();
    int getWidth();
    int getHeight();

private:
    int width, height, channels;
    GLuint texId;
};
