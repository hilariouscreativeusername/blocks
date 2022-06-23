#include "chunk.h"

#include "chunk_mesh_generator.h"

#include <random>

Chunk::Chunk(int x, int z) {
  // We have 2 options - 
  //   If the chunk has never bee loaded, generate it
  //   If the chunk has previously been loaded and saved to disk, load it from disk

  // TODO: Loading from disk

  // Generate chunk
  for (size_t x = 0; x < kChunkWidth; ++x) {
    for (size_t y = 0; y < kChunkHeight; ++y) {
      for (size_t z = 0; z < kChunkDepth; ++z) {
        blocks_[x + y * kChunkHeight + z * kChunkHeight * kChunkDepth] = rand() % 2 == 0 ? Block::kLog : Block::kLeaves;
      }
    }
  }

  vertex_array_ = GenerateMesh(blocks_);
}

void Chunk::Draw() {
  vertex_array_->Draw();
}
