#include "chunk.h"

#include "chunk_mesh_generator.h"

#include <random>

Chunk::Chunk(int chunkx, int chunky, int chunkz, Block* blocks) : chunkx_(chunkx), chunky_(chunky), chunkz_(chunkz), blocks_(blocks) {
  GenerateChunkMesh(blocks_, chunkx_, chunky_, chunkz_);
}

Chunk::~Chunk() {
  delete[] blocks_;
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
