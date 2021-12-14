#pragma once

#include "gl.h"

typedef int32_t ChunkPos;

class RenderChunk {

public:
    RenderChunk(ChunkPos inX, ChunkPos inY, ChunkPos inZ);
    ~RenderChunk();

    void renderSection();

private:
    int x, y, z;
    GLuint *buffer;
    bool loaded;

    void loadBuffer();
};
