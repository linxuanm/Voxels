#include "render_chunk.h"

#include <vector>

#include "util/specs.h"

RenderChunk::RenderChunk(ChunkPos inX, ChunkPos inY, ChunkPos inZ)
: loaded(false), x(inX), y(inY), z(inZ) {
    buffer = new GLuint[RENDER_LAYERS];
    idxBuf = new GLuint[RENDER_LAYERS];
    glGenBuffers(RENDER_LAYERS, buffer);
    glGenBuffers(RENDER_LAYERS, idxBuf);
}

RenderChunk::~RenderChunk() {
    glDeleteBuffers(RENDER_LAYERS, buffer);
    delete[] buffer;
}

void RenderChunk::bufferChunk() {
    if (!loaded) {
        loadBuffer();
    }


}

void RenderChunk::loadBuffer() {
    GLfloat pos[] = {
        -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, -1.0f, 1.0f, 0.0f,
        0.5f, 0.5f, -1.0f, 1.0f, 1.0f,
        -0.5f, 0.5f, -1.0f, 0.0f, 1.0f
    };

    GLuint indices[] = {
        0, 1, 2,
        2, 3, 0
    };

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

    loaded = true;
}
