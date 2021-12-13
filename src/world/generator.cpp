#include "generator.h"


Generator::Generator(): seed(42) {}

std::shared_ptr<Chunk> Generator::generateChunk(ChunkPos x, ChunkPos z) {
    std::shared_ptr<Chunk> chunk = std::make_shared<Chunk>();

    return chunk;
}
