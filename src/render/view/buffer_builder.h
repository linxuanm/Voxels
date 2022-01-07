#pragma once

#include <vector>

#include "gl.h"
#include "math/blockpos.h"

class Vertex {

public:
    Vertex(BlockPos, glm::vec2 uv, glm::vec3 normal);

private:
    GLfloat x, y, z;
    GLfloat u, v;
    GLfloat normX, normY, normZ;
};

class BufferBuilder {

public:
    void addVert(const Vertex &vert);
    void addIdxs(const std::initializer_list<GLsizei> &inIdxs);
    void drawBuffer(GLuint arrBuf, GLuint idxBuf);
    GLsizei getVertsOffset() const;
    GLsizei getElemCount() const;

    // Short-hand for drawing quad from the most recently
    // inserted 4 vertices.
    void drawQuad();

private:
    std::vector<Vertex> verts;
    std::vector<GLsizei> idxs;
};
