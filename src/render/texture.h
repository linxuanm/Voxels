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

#define BLOCKS_TEX_SIZE 256.0f
#define BLOCK_SIZE 16.0f
#define BLOCK_UV_OFFSET (BLOCK_SIZE / BLOCKS_TEX_SIZE)
#define BLOCK_UV_TL(U, V) (U * BLOCK_UV_OFFSET), (V * BLOCK_UV_OFFSET)
#define BLOCK_UV_TR(U, V) (U * BLOCK_UV_OFFSET), ((V+1) * BLOCK_UV_OFFSET)
#define BLOCK_UV_BL(U, V) ((U+1) * BLOCK_UV_OFFSET), (V * BLOCK_UV_OFFSET)
#define BLOCK_UV_BR(U, V) ((U+1) * BLOCK_UV_OFFSET), ((V+1) * BLOCK_UV_OFFSET)

typedef std::pair<int, int> BlockUV;

#define BLOCK_DIRT_UV BlockUV{0, 0}
#define BLOCK_STONE_UV BlockUV{1, 0}
#define BLOCK_GRASS_SIDE_UV BlockUV{2, 0}
#define BLOCK_GRASS_TOP_UV BlockUV{3, 0}
