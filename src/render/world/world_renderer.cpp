#include "world_renderer.h"

#include <string>

#include "gl.h"
#include "render/shader/shader.h"
#include "render/texture.h"

WorldRenderer::WorldRenderer() = default;

void WorldRenderer::init() {
    glGenVertexArrays(1, &skyVao);
}

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

    SkyboxShader &shader = Shaders::shaderSkybox();
    Textures::skyboxTexture().bind();

    //glDrawArrays(GL_TRIANGLES, 0, 36);

    glDepthMask(GL_TRUE);
}
