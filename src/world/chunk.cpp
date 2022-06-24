#include "chunk.h"

#include "chunk_mesh_generator.h"

#include <random>

Chunk::Chunk(int chunkx, int chunky, int chunkz) {
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
}

void Chunk::GenerateMesh() {
  if (vertex_array_) {
    delete vertex_array_;
  }
  vertex_array_ = GenerateChunkMesh(blocks_, chunkx_, chunky_, chunkz_);
}

void Chunk::Draw() {
  vertex_array_->Draw();
}
