#include "render_chunk.h"

#include "util/specs.h"

RenderChunk::RenderChunk() {
    buffer = new GLuint[RENDER_LAYERS];
    glGenBuffers(RENDER_LAYERS, buffer);
}

RenderChunk::~RenderChunk() {
    glDeleteBuffers(RENDER_LAYERS, buffer);
    delete[] buffer;
}
