#include "blockface.h"

BlockFace::Facing BlockFace::allFacing[6] = {
    UP, DOWN, WEST, EAST, NORTH, SOUTH
};

int BlockFace::facingVerts[6][4] = {
    {3, 2, 6, 7},
    {0, 1, 5, 4},
    {4, 0, 3, 7},
    {1, 5, 6, 2},
    {0, 1, 2, 3},
    {5, 4, 7, 6}
};

GLfloat BlockFace::vertOffset[8][3] = {
    {0, 0, 0},
    {1, 0, 0},
    {1, 1, 0},
    {0, 1, 0},
    {0, 0, 1},
    {1, 0, 1},
    {1, 1, 1},
    {0, 1, 1},
};

GLfloat BlockFace::faceUV[4][2] = {
    {0, 0}, {0, 1}, {1, 1}, {1, 0}
};

GLfloat BlockFace::facingNormal[6][3] = {
    { 0,  1,  0},
    { 0, -1,  0},
    {-1,  0,  0},
    { 1,  0,  0},
    { 0,  0, -1},
    { 0,  0,  1}
};
