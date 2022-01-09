#include "image_display.h"

#define STB_IMAGE_IMPLEMENTATION

#include <iostream>

#include "game/application.h"
#include "render/texture.h"
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

    Textures::blockTexture().bind();
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
