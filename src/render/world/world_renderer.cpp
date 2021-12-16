#include "world_renderer.h"

#include <string>

#include "gl.h"
#include "render/shader/shader.h"
#include "render/texture.h"

WorldRenderer::WorldRenderer() = default;

void WorldRenderer::init() {
    static Texture tex{"assets/texture/block/dirt.png"};
    tex.bind();
}

void WorldRenderer::drawWorld(World world, float deltaTime) {

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

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
