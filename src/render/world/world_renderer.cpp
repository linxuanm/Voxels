#include "world_renderer.h"

#include <string>

#include "gl.h"
#include "render/shader/shader.h"
#include "render/texture.h"

WorldRenderer::WorldRenderer() = default;

void WorldRenderer::init() {

    // TODO: fix facing of triangle to adapt to single side rendering
    GLfloat skyBox[36 * 3] = {
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

    GLfloat hudPos[4 * 5] = {
        0, 0, 0, 0, 0,
        1, 0, 0, 1, 0,
        1, 1, 0, 1, 1,
        0, 1, 0, 0, 1
    };

    // Sky Box
    glGenVertexArrays(1, &skyVao);
    glGenBuffers(1, &skyVbo);
    glBindVertexArray(skyVao);
    glBindBuffer(GL_ARRAY_BUFFER, skyVbo);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(
        0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, nullptr
    );

    glBufferData(
        GL_ARRAY_BUFFER, sizeof(skyBox),
        skyBox, GL_STATIC_DRAW
    );

    // GUI
    glGenVertexArrays(1, &hudVao);
    glGenBuffers(1, &hudVbo);
    glBindVertexArray(hudVao);
    glBindBuffer(GL_ARRAY_BUFFER, hudVbo);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(
        0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, nullptr
    );

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(
        1, 2, GL_FLOAT, GL_FALSE,
        sizeof(GLfloat) * 3, (void *) (3 * sizeof(GLfloat))
    );

    glBufferData(
        GL_ARRAY_BUFFER, sizeof(hudPos),
        hudPos, GL_STATIC_DRAW
    );

    glBindVertexArray(0);
}

WorldRenderer::~WorldRenderer() {
    glDeleteBuffers(1, &skyVbo);
    glDeleteVertexArrays(1, &skyVao);

    glDeleteBuffers(1, &hudVbo);
    glDeleteVertexArrays(1, &hudVao);
}

#include <iostream>
void WorldRenderer::drawWorld(World world, float deltaTime) {

    // TODO: draw skybox after cull testing
    drawSkybox();

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    Textures::blockTexture().bind();

    WorldOpaqueShader &shader = Shaders::shaderOpaque();
    shader.bind();
    shader.updateMVP(cam);

    Chunks &chunks = world.getChunks();
    for (auto &i: chunks) {
        i.second->renderChunk();
    }

    drawOverlay();
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

    glDrawArrays(GL_TRIANGLES, 0, 36);

    glBindVertexArray(0);

    glDepthMask(GL_TRUE);
}

void WorldRenderer::drawOverlay() {
    Textures::iconTexture().bind();
    HUDShader &shader = Shaders::shaderHUD();
    shader.bind();
    shader.updateOrtho();

    glBindVertexArray(hudVao);
    glDrawArrays(GL_TRIANGLES, 0, 4);
}
