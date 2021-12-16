#pragma once

#include "gl.h"
#include "render/view/buffer_builder.h"

typedef int32_t ChunkPos;
struct Vertex {
    GLfloat x, y, z;
    GLfloat u, v;
};


class RenderChunk {

public:
    RenderChunk(ChunkPos inX, ChunkPos inY, ChunkPos inZ);
    ~RenderChunk();

    void bufferChunk();

private:
    int x, y, z;
    GLuint *vao;
    GLuint *buffer;
    GLuint *idxBuf;

    bool loaded;
    size_t vertCount;

    void loadBuffer();
};
