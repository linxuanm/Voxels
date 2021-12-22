#include "world_renderer.h"

#include <glm/gtx/transform.hpp>
#include <string>

#include "game/application.h"
#include "gl.h"
#include "render/shader/shader.h"
#include "render/texture.h"
#include "util/config.h"
#include "game/voxels.h"

WorldRenderer::WorldRenderer() = default;

void WorldRenderer::init() {

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
    glGenVertexArrays(1, &boxVao);
    glGenBuffers(1, &boxVbo);
    glBindVertexArray(boxVao);
    glBindBuffer(GL_ARRAY_BUFFER, boxVbo);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(
        0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, nullptr
    );

    glBufferData(
        GL_ARRAY_BUFFER, sizeof(BlockFace::cubeVertexDraw),
        BlockFace::cubeVertexDraw, GL_STATIC_DRAW
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
    glDeleteBuffers(1, &boxVbo);
    glDeleteVertexArrays(1, &boxVao);

    glDeleteBuffers(1, &hudVbo);
    glDeleteVertexArrays(1, &hudVao);
}

void WorldRenderer::drawWorld(World &world, float deltaTime) {

    // TODO: draw skybox after cull testing
    glBindVertexArray(boxVao);
    drawSkybox();
    glBindVertexArray(0);

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

    glBindVertexArray(boxVao);
    drawWorldOverlay();
    glBindVertexArray(0);

    drawOverlay();
}

Camera &WorldRenderer::camera() {
    return cam;
}

void WorldRenderer::drawSkybox() {
    glDepthMask(GL_FALSE);

    Textures::skyboxTexture().bind();
    SkyboxShader &shader = Shaders::shaderSkybox();
    shader.bind();
    shader.updateMVP(cam);

    glDrawArrays(GL_TRIANGLES, 0, 36);

    glDepthMask(GL_TRUE);
}

void WorldRenderer::drawOverlay() {
    Textures::iconTexture().bind();
    SimpleShader &shader = Shaders::shaderSimple();
    shader.bind();
    shader.updateColor({1.0f, 1.0f, 1.0f, 1.0f});
    shader.updateMVP(Application::orthoViewMat);

    glEnable(GL_BLEND);
    glBlendFuncSeparate(
        GL_ONE_MINUS_DST_COLOR, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO
    );

    glBindVertexArray(hudVao);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glDisable(GL_BLEND);
}

void WorldRenderer::drawWorldOverlay() {
    RayResult result = Voxels::get().getMouseOver();
    if (result.hit) {
        glm::vec3 pos = result.pos.toVec() + glm::vec3{0.5f, 0.5f, 0.5f};
        glm::mat4 scaleMat = glm::scale(glm::vec3{0.501f, 0.501f, 0.501f});
        glm::mat4 transMat = glm::translate(pos);

        float alpha = (float) glm::sin(glfwGetTime() * 2.5f) * 0.1f;
        alpha += 0.3f;

        SimpleShader &shader = Shaders::shaderColor();
        shader.bind();
        shader.updateColor({1.0f, 1.0f, 1.0f, alpha});
        shader.updateMVP(cam.getViewProjMat() * transMat * scaleMat);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glDrawArrays(GL_TRIANGLES, 0, 36);

        glDisable(GL_BLEND);
    }
}
