#include "model.h"

#include <iostream>

// Adds a face with UV coords from the blocks texture map.
static void addFace(
    BufferBuilder &buffer, const BlockPos &pos,
    BlockFace::Facing face, const BlockUV &blockUV
    ) {
    for (int i = 0; i < 4; i++) {
        int vertId = BlockFace::facingVerts[face][i];
        auto currOffset = BlockFace::vertOffset[vertId];
        auto uv = BlockFace::getFaceUV(i, blockUV);
        auto norm = BlockFace::facingNormal[face];

        // TODO: add a vertex format
        buffer.addVert({
            pos + currOffset, uv,
            glm::vec3{norm[0], norm[1], norm[2]}
        });
    }

    buffer.drawQuad();
}

SixFaceModel::SixFaceModel(const BlockUV &inUV): uv(inUV) {}

void SixFaceModel::buffer(BufferBuilder &buf, BlockPos pos, bool exposed[6]) {
    for (auto &face: BlockFace::allFacing) {
        if (exposed[face]) {
            addFace(buf, pos, face, uv);
        }
    }
}

FourFaceModel::FourFaceModel(
    const BlockUV &inTopUV,
    const BlockUV &inSideUV,
    const BlockUV &inBottomUV
    ): topUV(inTopUV), sideUV(inSideUV), bottomUV(inBottomUV) {}

void FourFaceModel::buffer(BufferBuilder &buf, BlockPos pos, bool *exposed) {
    if (exposed[BlockFace::UP]) addFace(buf, pos, BlockFace::UP, topUV);
    if (exposed[BlockFace::DOWN]) addFace(buf, pos, BlockFace::DOWN, bottomUV);

    for (auto &face: BlockFace::cardinalFacing) {
        if (exposed[face]) {
            addFace(buf, pos, face, sideUV);
        }
    }
}
