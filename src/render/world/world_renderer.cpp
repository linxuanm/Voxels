#include "world_renderer.h"

#include <string>

#include "gl.h"
#include "render/shader/shader.h"
#include "render/texture.h"

WorldRenderer::WorldRenderer() = default;

void WorldRenderer::init() {
    /*GLfloat pos[] = {
        -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, -1.0f, 1.0f, 0.0f, // correct
        0.5f, 0.5f, -1.0f, 1.0f, 1.0f,
        -0.5f, 0.5f, -1.0f, 0.0f, 1.0f // correct
    };

    GLuint indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    std::string vertSrc = "assets/shader/default.vert";
    std::string fragSrc = "assets/shader/default.frag";

    GLuint buf;
    glGenBuffers(1, &buf);
    glBindBuffer(GL_ARRAY_BUFFER, buf);
    glBufferData(GL_ARRAY_BUFFER, sizeof(pos), pos, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, buf);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 5, nullptr);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 5, (void *) 12);

    GLuint indexBuf;
    glGenBuffers(1, &indexBuf);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuf);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glBindVertexArray(0);

    static Shader shader{vertSrc, fragSrc};
    shader.bind();

    static Texture tex{"assets/texture/block/dirt.png"};
    tex.bind();

    varTex = shader.getUniformLocation((char *) "texSampler");
    varMVP = shader.getUniformLocation((char *) "MVP");

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);*/

    static Texture tex{"assets/texture/block/dirt.png"};
    tex.bind();

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
}

void WorldRenderer::drawWorld(World world, float deltaTime) {
    WorldOpaqueShader &shader = Shaders::shaderOpaque();
    shader.bind();
    shader.updateMVP(cam);
    shader.setTexSampler(0);

    ChunkMap &chunks = world.chunkMap();
    for (auto &i: chunks) {
        auto x = (int32_t) (i.first >> 32);
        auto z = (int32_t) (i.first & 0xFFFFFFFF);

        i.second->renderChunk();
    }
}

Camera &WorldRenderer::camera() {
    return cam;
}
