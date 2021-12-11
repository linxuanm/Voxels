#pragma once

#include <string>
#include <GL/glew.h>

class Texture {

public:
    Texture(std::string path);
    ~Texture();

    void bind();
    int getWidth();
    int getHeight();

private:
    int width, height, channels;
    GLuint texId;
};
