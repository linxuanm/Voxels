#pragma once

#include "gl.h"
#include "render/view/buffer_builder.h"

typedef int32_t ChunkPos;
struct Vertex {
    int x, y, z;
    float u, v;
};


class RenderChunk {

public:
    RenderChunk(ChunkPos inX, ChunkPos inY, ChunkPos inZ);
    ~RenderChunk();

    void bufferChunk(int &vertCount);

private:
    int x, y, z;
    GLuint *buffer;
    GLuint *idxBuf;

    bool loaded;
    int sectionVertCount;

    void loadBuffer();
};
