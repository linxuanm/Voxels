#include "model.h"

// Adds a face with UV coords from the blocks texture map.
static void addFace(
    BufferBuilder &buffer, const BlockPos &pos,
    BlockFace::Facing face, int u, int v
    ) {
    for (int i = 0; i < 4; i++) {
        int vertId = BlockFace::facingVerts[face][i];
        auto currOffset = BlockFace::vertOffset[vertId];
        auto uv = BlockFace::getFaceUV(i, u, v);
        auto norm = BlockFace::facingNormal[face];

        // TODO: add a vertex format
        buffer.addVert({
            pos + currOffset, uv,
            glm::vec3{norm[0], norm[1], norm[2]}
        });
    }

    buffer.drawQuad();
}

SixFaceModel::SixFaceModel(int inU, int inV): u(inU), v(inV) {}

void SixFaceModel::buffer(BufferBuilder &buf, BlockPos pos, bool exposed[6]) {
    for (auto &face: BlockFace::allFacing) {
        if (exposed[face]) {
            addFace(buf, pos, face, u, v);
        }
    }
}
