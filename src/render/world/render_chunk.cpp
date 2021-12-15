#include "render_chunk.h"

#include <vector>
#include <render/shader/shader.h>

#include "util/specs.h"

RenderChunk::RenderChunk(ChunkPos inX, ChunkPos inY, ChunkPos inZ)
: loaded(false), sectionVertCount(0), x(inX), y(inY), z(inZ) {
    vao = new GLuint[RENDER_LAYERS];
    buffer = new GLuint[RENDER_LAYERS];
    idxBuf = new GLuint[RENDER_LAYERS];
    glGenVertexArrays(RENDER_LAYERS, vao);
    glGenBuffers(RENDER_LAYERS, buffer);
    glGenBuffers(RENDER_LAYERS, idxBuf);
}

RenderChunk::~RenderChunk() {
    glDeleteVertexArrays(RENDER_LAYERS, vao);
    glDeleteBuffers(RENDER_LAYERS, buffer);
    glDeleteBuffers(RENDER_LAYERS, idxBuf);
    delete[] vao;
    delete[] buffer;
    delete[] idxBuf;
}

void RenderChunk::bufferChunk() {
    if (!loaded) {
        loadBuffer();
    }

    glBindVertexArray(vao[0]);

    WorldOpaqueShader &shader = Shaders::shaderOpaque();
    shader.setOffset({x, y, z});

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}

void RenderChunk::loadBuffer() {
    GLfloat pos[] = {
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // correct
        1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 0.0f, 1.0f // correct
    };

    GLuint indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    glBindVertexArray(vao[0]);

    glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(pos), pos, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 5, nullptr);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(
        1, 2, GL_FLOAT, GL_FALSE,
        sizeof(GLfloat) * 5, (void *) (sizeof(GLfloat) * 3)
    );

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, idxBuf[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glBindVertexArray(0);

    loaded = true;
}
