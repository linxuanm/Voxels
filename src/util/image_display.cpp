#include "image_display.h"

#define STB_IMAGE_IMPLEMENTATION

#include <iostream>

#include "game/application.h"
#include "render/shader/shader.h"
#include "util/log.h"

void Testing::drawQuadLoop(float size) {
    GLuint vao, vbo;
    GLfloat quadPos[6 * 5] = {
        -size, -size, 0, 0, 0,
         size, -size, 0, 1, 0,
         size,  size, 0, 1, 1,

         size,  size, 0, 1, 1,
        -size,  size, 0, 0, 1,
        -size, -size, 0, 0, 0
    };

    glfwSwapBuffers(Application::window); // Mac OS

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(
        0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 5, nullptr
    );

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(
        1, 2, GL_FLOAT, GL_FALSE,
        sizeof(GLfloat) * 5, (void *) (3 * sizeof(GLfloat))
    );

    glBufferData(
        GL_ARRAY_BUFFER, sizeof(quadPos),
        quadPos, GL_STATIC_DRAW
    );

    SimpleShader &shader = Shaders::shaderSimple();
    shader.bind();
    shader.updateColor({1.0f, 1.0f, 1.0f, 1.0f});
    shader.updateMVP(Application::orthoViewMat);

    auto deltaTime = (float) glfwGetTime();
    float lastFrame = deltaTime;

    while (!glfwWindowShouldClose(Application::window)) {
        auto currTime = (float) glfwGetTime();
        deltaTime = currTime - lastFrame;
        lastFrame = currTime;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        glfwSwapBuffers(Application::window);
        glfwPollEvents();

        Log::logGLError();
    }

    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
}

TexPtr Testing::genNoiseTex(NoiseSampler sampler, int width, int height) {
    auto *buf = new uint32_t[width * height];
    for (int h = 0; h < height; h++) {
        for (int w = 0; w < width; w++) {
            float u = (float) w / width;
            float v = (float) h / height;

            float noise = sampler(u, v);
            auto p = static_cast<uint32_t>(noise * 255);
            buf[h * height + w] = (255 << 24) | (p << 16) | (p << 8) | p;
        }
    }

    GLuint texId;
    glGenTextures(1, &texId);
    glBindTexture(GL_TEXTURE_2D, texId);

    glTexImage2D(
        GL_TEXTURE_2D, 0, GL_RGBA, width, height,
        0, GL_RGBA, GL_UNSIGNED_BYTE, buf
    );

    TexPtr ptr = std::make_unique<Texture>(width, height, 4, texId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    delete[] buf;

    return ptr;
}
