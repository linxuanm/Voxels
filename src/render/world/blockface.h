#pragma once

#include <glm/glm.hpp>

#include "gl.h"

namespace BlockFace {

    enum Facing {
        UP, DOWN, WEST, EAST, NORTH, SOUTH
    };

    extern Facing allFacing[6];
    extern int facingVerts[6][4];
    extern GLfloat vertOffset[8][3];
    extern GLfloat faceUV[4][2];
    extern GLfloat facingNormal[6][3];
};
