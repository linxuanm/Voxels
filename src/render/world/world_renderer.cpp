#include "world_renderer.h"

#include <string>

#include "gl.h"
#include "render/shader/shader.h"
#include "render/texture.h"

WorldRenderer::WorldRenderer() = default;

void WorldRenderer::init() {

    // TODO: fix facing of triangle to adapt to single side rendering
    GLfloat pos[36 * 3] = {
        -1, -1, -1,
         1, -1, -1,
         1,  1, -1,
         1,  1, -1,
        -1,  1, -1,
        -1, -1, -1,

        -1, -1,  1,
         1, -1,  1,
         1,  1,  1,
         1,  1,  1,
        -1,  1,  1,
        -1, -1,  1,

        -1, -1, -1,
        -1, -1,  1,
         1, -1,  1,
         1, -1,  1,
         1, -1, -1,
        -1, -1, -1,

        -1,  1, -1,
        -1,  1,  1,
         1,  1,  1,
         1,  1,  1,
         1,  1, -1,
        -1,  1, -1,

        -1, -1, -1,
        -1, -1,  1,
        -1,  1,  1,
        -1,  1,  1,
        -1,  1, -1,
        -1, -1, -1,

         1, -1, -1,
         1, -1,  1,
         1,  1,  1,
         1,  1,  1,
         1,  1, -1,
         1, -1, -1,
    };

    glGenVertexArrays(1, &skyVao);
    glGenBuffers(1, &skyVbo);

    glBindVertexArray(skyVao);
    glBindBuffer(GL_ARRAY_BUFFER, skyVbo);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(
        0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, nullptr
    );

    glBufferData(
        GL_ARRAY_BUFFER, sizeof(pos),
        pos, GL_STATIC_DRAW
    );

    glBindVertexArray(0);
}

WorldRenderer::~WorldRenderer() {
    glDeleteBuffers(1, &skyVbo);
    glDeleteVertexArrays(1, &skyVao);
}

#include <iostream>
void WorldRenderer::drawWorld(World world, float deltaTime) {
    drawSkybox();

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    Textures::blockTexture().bind();

    WorldOpaqueShader &shader = Shaders::shaderOpaque();
    shader.bind();
    shader.updateMVP(cam);
    shader.setTexSampler(0);

    Chunks &chunks = world.getChunks();
    for (auto &i: chunks) {
        i.second->renderChunk();
    }
}

Camera &WorldRenderer::camera() {
    return cam;
}

void WorldRenderer::drawSkybox() {
    glDepthMask(GL_FALSE);

    glBindVertexArray(skyVao);

    Textures::skyboxTexture().bind();
    SkyboxShader &shader = Shaders::shaderSkybox();
    shader.bind();
    shader.updateMVP(cam);
    shader.setTexSampler(0);

    glDrawArrays(GL_TRIANGLES, 0, 36);

    glBindVertexArray(0);

    glDepthMask(GL_TRUE);
}
