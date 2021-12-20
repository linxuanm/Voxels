#pragma once

#include <string>
#include <vector>

#include "gl.h"

class Texture {

public:
    explicit Texture(std::string path);
    explicit Texture(std::vector<std::string> paths); // cubemap
    ~Texture();

    void bind();
    int getWidth();
    int getHeight();

private:
    int width, height, channels;
    GLuint texId;
    bool cube;
};

namespace Textures {
    Texture &blockTexture();
    Texture &skyboxTexture();
    Texture &iconTexture();
};

// Texture UVs
#define ICONS_CROSSHAIR 0
#define ICONS_CROSSHAIR_SIZE 32
