#pragma once

#include "gl.h"

typedef int32_t ChunkPos;

class RenderChunk {

public:
    RenderChunk(ChunkPos inX, ChunkPos inY, ChunkPos inZ);
    ~RenderChunk();

    void bufferChunk();

private:
    int x, y, z;
    GLuint *buffer;
    GLuint *idxBuf;
    bool loaded;

    void loadBuffer();
};
