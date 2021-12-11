#include "texture.h"

#include <fstream>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Texture::Texture(std::string path) {
    std::ifstream file{path};

    if (!file.good()) {
        std::cout << "[Shader] FILE \"" << path;
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
}

Texture::~Texture() {
    glDeleteTextures(1, &texId);
}

void Texture::bind() {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texId);
}

int Texture::getWidth() {
    return width;
}

int Texture::getHeight() {
    return height;
}
