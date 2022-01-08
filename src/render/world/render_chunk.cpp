#include "render_chunk.h"

#include <iostream>

#include "render/shader/shader.h"
#include "render/texture.h"
#include "world/chunk.h"
#include "world/blocks.h"
#include "world/world.h"
#include "util/specs.h"
#include "game/voxels.h"

RenderChunk::RenderChunk(): initialized(false) {}

RenderChunk::RenderChunk(Chunk *c, ChunkPos inX, ChunkPos inY, ChunkPos inZ)
: dead(false), initialized(false), vertCount(0), updated(false)
, chunk(c), x(inX), y(inY), z(inZ) {}

void RenderChunk::tryInitGL() {
    if (initialized) return;

    glGenVertexArrays(RENDER_LAYERS, &vao[0]);
    glGenBuffers(RENDER_LAYERS, &arrBuf[0]);
    glGenBuffers(RENDER_LAYERS, &idxBuf[0]);

    glBindVertexArray(vao[0]);

    glBindBuffer(GL_ARRAY_BUFFER, arrBuf[0]);
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

void RenderChunk::bufferChunk() {
    if (dead) return;

    if (!updated) {
        loadBuffer();
    }

    glBindVertexArray(vao[0]);

    WorldOpaqueShader &shader = Shaders::shaderOpaque();
    shader.setOffset({x, y, z});

    glDrawElements(GL_TRIANGLES, vertCount, GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}

void RenderChunk::loadBuffer() {
    BufferBuilder buffer;

    for (int h = 0; h < 16; h++) {
        for (int i = 0; i < 16; i++) {
            for (int j = 0; j < 16; j++) {
                BlockPos relPos{i, h, j};
                BlockPos absHeightPos = relPos + BlockPos{0, y << 4, 0};
                BlockRef block = chunk->getBlockRel(absHeightPos);

                if (!block->isAir()) {
                    for (auto &face: BlockFace::allFacing) {
                        if (shouldRenderFace(absHeightPos, face)) {
                            addFace(relPos, face, buffer);
                        }
                    }
                }
            }
        }
    }

    glBindVertexArray(vao[0]);
    buffer.drawBuffer(arrBuf[0], idxBuf[0]);
    glBindVertexArray(0);

    updated = true;
    vertCount = buffer.getElemCount();
}

void RenderChunk::addFace(
    const BlockPos &pos, BlockFace::Facing face,
    BufferBuilder &buffer) {

    for (int i = 0; i < 4; i++) {
        int vertId = BlockFace::facingVerts[face][i];
        auto currOffset = BlockFace::vertOffset[vertId];
        auto uv = BlockFace::getFaceUV(i, BLOCK_STONE_U, BLOCK_STONE_V);
        auto norm = BlockFace::facingNormal[face];

        // TODO: add a vertex format
        buffer.addVert({
            pos + currOffset, uv,
            glm::vec3{norm[0], norm[1], norm[2]}
        });
    }

    buffer.drawQuad();
}

bool RenderChunk::shouldRenderFace(BlockPos pos, BlockFace::Facing face) {
    BlockPos side = pos.offset(face);

    if (side.y() > CHUNK_HEIGHT || side.y() < 0) {
        return true;
    }

    BlockRef block;
    if (side.x() < 0 || side.x() >= 16 || side.z() < 0 || side.z() >= 16) {
        block = chunk->getWorld().getBlock(side + BlockPos{x << 4, 0, z << 4});
    } else {
        block = chunk->getBlockRel(side);
    }

    return !block->isSolid();
}

void RenderChunk::refresh() {
    updated = false;
}

void RenderChunk::setDead() {
    dead = true;

    glDeleteBuffers(RENDER_LAYERS, &arrBuf[0]);
    glDeleteBuffers(RENDER_LAYERS, &idxBuf[0]);
    glDeleteVertexArrays(RENDER_LAYERS, &vao[0]);
}
