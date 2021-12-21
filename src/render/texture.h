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

#define ICONS_SIZE 256.0f
#define ICONS_CROSS_SIZE 16.0f
#define ICONS_CROSS_X 0.0f
#define ICONS_CROSS_Y 0.0f
#define ICONS_CROSS_XX (ICONS_CROSS_X + ICONS_CROSS_SIZE / ICONS_SIZE)
#define ICONS_CROSS_YY (ICONS_CROSS_Y + ICONS_CROSS_SIZE / ICONS_SIZE)
