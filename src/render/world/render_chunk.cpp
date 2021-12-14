#include "render_chunk.h"

#include "util/specs.h"

RenderChunk::RenderChunk(ChunkPos inX, ChunkPos inY, ChunkPos inZ)
: loaded(false), x(inX), y(inY), z(inZ) {
    buffer = new GLuint[RENDER_LAYERS];
    glGenBuffers(RENDER_LAYERS, buffer);
}

RenderChunk::~RenderChunk() {
    glDeleteBuffers(RENDER_LAYERS, buffer);
    delete[] buffer;
}

void RenderChunk::renderSection() {
    if (!loaded) {
        loadBuffer();
    }


}

void RenderChunk::loadBuffer() {

}
