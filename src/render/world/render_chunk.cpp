#include "render_chunk.h"

#include <iostream>

#include "render/shader/shader.h"
#include "world/chunk.h"
#include "world/blocks.h"
#include "world/world.h"
#include "util/specs.h"
#include "game/voxels.h"

Vertex::Vertex(BlockPos pos, glm::vec2 uv, glm::vec3 normal)
: x(pos.x()), y(pos.y()), z(pos.z())
, u(uv.x), v(uv.y)
, normX(normal.x), normY(normal.y), normZ(normal.z) {}

RenderChunk::RenderChunk() = default;

RenderChunk::RenderChunk(Chunk *c, ChunkPos inX, ChunkPos inY, ChunkPos inZ)
: notEmpty(true), dead(false), initialized(false), vertCount(0)
, loaded(false), chunk(c), x(inX), y(inY), z(inZ) {

    vao = new GLuint[RENDER_LAYERS];
    buffer = new GLuint[RENDER_LAYERS];
    idxBuf = new GLuint[RENDER_LAYERS];
}

void RenderChunk::tryInitGL() {
    if (initialized) return;

    glGenVertexArrays(RENDER_LAYERS, vao);
    glGenBuffers(RENDER_LAYERS, buffer);
    glGenBuffers(RENDER_LAYERS, idxBuf);

    glBindVertexArray(vao[0]);

    glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(
        1, 2, GL_FLOAT, GL_FALSE,
        sizeof(Vertex), (void *) (sizeof(GLfloat) * 3)
    );

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(
        2, 3, GL_FLOAT, GL_FALSE,
        sizeof(Vertex), (void *) (sizeof(GLfloat) * 5)
    );

    glBindVertexArray(0);

    initialized = true;
}

RenderChunk::~RenderChunk() {
    if (initialized) {
        glDeleteBuffers(RENDER_LAYERS, buffer);
        glDeleteBuffers(RENDER_LAYERS, idxBuf);
        glDeleteVertexArrays(RENDER_LAYERS, vao);

        /*
         * Copy constructor is still enabled for RenderChunk
         * for potential dummy chunks; however, the array
         * pointers would then be shared among both objects.
         *
         * This is a temporary hacky way of resolving this;
         * vectors will be used later when render layers are added.
         */
        if (notEmpty) {
            delete[] buffer;
            delete[] idxBuf;
            delete[] vao;
        }
    }
}

void RenderChunk::bufferChunk() {
    if (dead) return;

    if (!loaded) {
        loadBuffer();
    }

    glBindVertexArray(vao[0]);

    WorldOpaqueShader &shader = Shaders::shaderOpaque();
    shader.setOffset({x, y, z});

    glDrawElements(GL_TRIANGLES, vertCount, GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}

void RenderChunk::loadBuffer() {
    std::vector<Vertex> verts;
    std::vector<int> idxs;

    for (int h = 0; h < 16; h++) {
        for (int i = 0; i < 16; i++) {
            for (int j = 0; j < 16; j++) {
                BlockPos relPos{i, h, j};
                BlockPos absHeightPos = relPos + BlockPos{0, y << 4, 0};
                int block = chunk->getBlockRel(absHeightPos);

                if (block != BLOCK_AIR) {
                    for (auto &f: BlockFace::allFacing) {
                        if (shouldRenderFace(absHeightPos, f)) {
                            addFace(BLOCK_DIRT, relPos, f, verts, idxs);
                        }
                    }
                }
            }
        }
    }

    glBindVertexArray(vao[0]);

    glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
    glBufferData(
        GL_ARRAY_BUFFER, verts.size() * sizeof(Vertex),
        &verts[0], GL_STATIC_DRAW
    );

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, idxBuf[0]);
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER, idxs.size() * sizeof(Vertex),
        &idxs[0], GL_STATIC_DRAW
    );

    glBindVertexArray(0);

    loaded = true;
    vertCount = (GLsizei) idxs.size();
}

void RenderChunk::addFace(
    int block, const BlockPos &pos, BlockFace::Facing face,
    std::vector<Vertex> &verts, std::vector<GLsizei> &idxs) {

    auto offset = (GLsizei) verts.size();
    for (int i = 0; i < 4; i++) {
        int vertId = BlockFace::facingVerts[face][i];
        auto currOffset = BlockFace::vertOffset[vertId];
        auto uv = BlockFace::faceUV[i];
        auto norm = BlockFace::facingNormal[face];

        // TODO: add a vertex format
        verts.emplace_back(
            pos + currOffset,
            glm::vec2{uv[0], uv[1]},
            glm::vec3{norm[0], norm[1], norm[2]}
        );
    }

    idxs.insert(idxs.end(), {
        0 + offset, 1 + offset, 2 + offset,
        2 + offset, 3 + offset, 0 + offset
    });
}

bool RenderChunk::shouldRenderFace(BlockPos pos, BlockFace::Facing face) {
    BlockPos side = pos.offset(face);

    if (side.y() > CHUNK_HEIGHT || side.y() < 0) {
        return true;
    }

    int block;
    if (side.x() < 0 || side.x() >= 16 || side.z() < 0 || side.z() >= 16) {
        block = chunk->getWorld().getBlock(side + BlockPos{x << 4, 0, z << 4});
    } else {
        block = chunk->getBlockRel(side);
    }

    return !Blocks::isSolid(block);
}

void RenderChunk::refresh() {
    loaded = false;
}

void RenderChunk::setDead() {
    dead = true;
}
