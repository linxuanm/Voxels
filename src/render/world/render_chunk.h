#pragma once

#include "gl.h"

class RenderChunk {

public:
    RenderChunk();
    ~RenderChunk();

private:
    GLuint *buffer;
};
