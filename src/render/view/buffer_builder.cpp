#include "buffer_builder.h"

Vertex::Vertex(BlockPos pos, glm::vec2 uv, glm::vec3 normal)
: x(pos.x()), y(pos.y()), z(pos.z())
, u(uv.x), v(uv.y)
, normX(normal.x), normY(normal.y), normZ(normal.z) {}

void BufferBuilder::addIdxs(const std::initializer_list<GLsizei> &inIdxs) {
    idxs.insert(idxs.end(), inIdxs);
}

void BufferBuilder::addVert(const Vertex &vert) {
    verts.push_back(vert);
}

void BufferBuilder::drawQuad() {
    auto offset = static_cast<GLsizei>(verts.size());
    idxs.insert(idxs.end(), {
        offset - 4, offset - 3, offset - 2,
        offset - 2, offset - 1, offset - 4
    });
}

GLsizei BufferBuilder::getVertsOffset() const {
    return static_cast<GLsizei>(verts.size());
}

GLsizei BufferBuilder::getElemCount() const {
    return static_cast<GLsizei>(idxs.size());
}

void BufferBuilder::drawBuffer(GLuint arrBuf, GLuint idxBuf) {
    glBindBuffer(GL_ARRAY_BUFFER, arrBuf);
    glBufferData(
        GL_ARRAY_BUFFER, verts.size() * sizeof(Vertex),
        &verts[0], GL_STATIC_DRAW
    );

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, idxBuf);
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER, idxs.size() * sizeof(Vertex),
        &idxs[0], GL_STATIC_DRAW
    );
}
