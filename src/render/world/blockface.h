#pragma once

#include <glm/glm.hpp>

#include "gl.h"
#include "render/texture.h"

namespace BlockFace {

    enum Facing {
        UP, DOWN, WEST, EAST, NORTH, SOUTH
    };

    extern Facing allFacing[6];
    extern Facing cardinalFacing[4];
    extern int facingVerts[6][4];
    extern GLfloat vertOffset[8][3];
    extern GLfloat facingNormal[6][3];
    extern GLfloat cubeVertexDraw[36 * 3];

    glm::vec2 getFaceUV(int vert, const BlockUV &uv);
};
