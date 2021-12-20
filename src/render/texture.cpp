#include "texture.h"

#include <fstream>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Texture::Texture(std::string path): cube(false) {
    std::ifstream file{path};

    if (!file.good()) {
        std::cout << "[Texture] FILE \"" << path;
        std::cout << "\" DOES NOT EXIST" << std::endl;
        return;
    }

    glGenTextures(1, &texId);
    glBindTexture(GL_TEXTURE_2D, texId);

    stbi_set_flip_vertically_on_load(1);
    stbi_uc *buffer = stbi_load(path.c_str(), &width, &height, &channels, 4);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(
        GL_TEXTURE_2D, 0, GL_RGBA8, width, height,
        0, GL_RGBA, GL_UNSIGNED_BYTE, buffer
    );

    stbi_image_free(buffer);
}

Texture::Texture(std::vector<std::string> paths): cube(true) {
    glGenTextures(1, &texId);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texId);

    for (int i = 0; i < paths.size(); i++) {
        stbi_uc *buffer = stbi_load(
            paths[i].c_str(), &width, &height, &channels, 0
        );

        if (!buffer) {
            std::cout << "[Texture] FILE \"" << paths[i];
            std::cout << "\" DOES NOT EXIST" << std::endl;

            stbi_image_free(buffer);
            return;
        }

        glTexImage2D(
            (GLenum) (GL_TEXTURE_CUBE_MAP_POSITIVE_X + i), 0, GL_RGB,
            width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, buffer
        );
        stbi_image_free(buffer);
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

Texture::~Texture() {
    glDeleteTextures(1, &texId);
}

void Texture::bind() {
    glActiveTexture(GL_TEXTURE0);
    if (cube) {
        glBindTexture(GL_TEXTURE_CUBE_MAP, texId);
    } else {
        glBindTexture(GL_TEXTURE_2D, texId);
    }
}

int Texture::getWidth() {
    return width;
}

int Texture::getHeight() {
    return height;
}

Texture &Textures::blockTexture() {
    static Texture tex{"assets/texture/block/dirt.png"};
    return tex;
}

Texture &Textures::skyboxTexture() {
    std::vector<std::string> paths{
        "assets/texture/skybox/sky_right.bmp",
        "assets/texture/skybox/sky_left.bmp",
        "assets/texture/skybox/sky_top.bmp",
        "assets/texture/skybox/sky_down.bmp",
        "assets/texture/skybox/sky_front.bmp",
        "assets/texture/skybox/sky_back.bmp",
    };
    static Texture tex{paths};
    return tex;
}

Texture &Textures::iconTexture() {
    static Texture tex{"assets/texture/gui/icons.png"};
    return tex;
}
