#include "world_renderer.h"

#include <string>

#include "gl.h"
#include "render/shader/shader.h"
#include "render/texture.h"
#include "util/config.h"

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

    const GLfloat size = Config::crosshairSize;
    GLfloat hudPos[6 * 5] = {
        -size, -size, 0, ICONS_CROSS_X, ICONS_CROSS_Y,
         size, -size, 0, ICONS_CROSS_XX, ICONS_CROSS_Y,
         size,  size, 0, ICONS_CROSS_XX, ICONS_CROSS_YY,

         size,  size, 0, ICONS_CROSS_XX, ICONS_CROSS_YY,
        -size,  size, 0, ICONS_CROSS_X, ICONS_CROSS_YY,
        -size, -size, 0, ICONS_CROSS_X, ICONS_CROSS_Y
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
        0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 5, nullptr
    );

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(
        1, 2, GL_FLOAT, GL_FALSE,
        sizeof(GLfloat) * 5, (void *) (3 * sizeof(GLfloat))
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

    glEnable(GL_BLEND);
    //glBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_ONE_MINUS_SRC_COLOR);
    glBlendFuncSeparate(GL_ONE_MINUS_DST_COLOR, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);

    glBindVertexArray(hudVao);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glDisable(GL_BLEND);
}
