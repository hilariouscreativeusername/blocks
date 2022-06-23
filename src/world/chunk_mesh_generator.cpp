#include "chunk_mesh_generator.h"

#include <vector>

#include <glm/glm.hpp>

#include "chunk.h"

VertexArray* GenerateMesh(Block* blocks) {
  // Non-indexed size of one face = 120 bytes
  //                 Indexed size = 104 bytes

  // All sizes in floats
  constexpr size_t kVertexSize         = 5;
  constexpr size_t kUniqueQuadVertices = 4;
  constexpr size_t kQuadSizeVertices   = kUniqueQuadVertices * kVertexSize;
  constexpr size_t kMaxBlockVertices   = kQuadSizeVertices * 6;
  constexpr size_t kChunkSize          = kChunkWidth * kChunkHeight * kChunkDepth;
  constexpr size_t kMaxVertices        = kChunkSize * kMaxBlockVertices;
  // Max size of vertices in GPU memory ~2MB
  std::vector<float> vertices(kMaxVertices);

  // Size in unsigned ints
  constexpr size_t kQuadSizeIndices = 6;
  constexpr size_t kBlockMaxQuads   = 6;
  constexpr size_t kMaxIndices = kChunkSize * kQuadSizeIndices * kBlockMaxQuads;
  std::vector<unsigned int> indices(kMaxIndices);
  // Max size of indices in GPU memory ~100KB

  size_t num_allocated_quads = 0;

  auto allocate_quad_indices = [&]() {
    const size_t kIndexOffset = num_allocated_quads * kQuadSizeIndices;
    const size_t kCurrentVertexIndex = kUniqueQuadVertices * num_allocated_quads;
    indices[kIndexOffset + 0] = kCurrentVertexIndex + 0;
    indices[kIndexOffset + 1] = kCurrentVertexIndex + 3;
    indices[kIndexOffset + 2] = kCurrentVertexIndex + 1;
    indices[kIndexOffset + 3] = kCurrentVertexIndex + 1;
    indices[kIndexOffset + 4] = kCurrentVertexIndex + 3;
    indices[kIndexOffset + 5] = kCurrentVertexIndex + 2;
    ++num_allocated_quads;
  };

  auto allocate_quad_uvs = [&](size_t vertex_offset){
    vertices[vertex_offset  + 3] = 1.0f;
    vertices[vertex_offset  + 4] = 0.0f;
    vertices[vertex_offset  + 8] = 1.0f;
    vertices[vertex_offset  + 9] = 1.0f;
    vertices[vertex_offset + 13] = 0.0f;
    vertices[vertex_offset + 14] = 1.0f;
    vertices[vertex_offset + 18] = 0.0f;
    vertices[vertex_offset + 19] = 0.0f;
  };

  // South = +Z,  North = -Z
  // East  = +X,  West  = -X
  // Down  = -Y,  Up    = +Y
  enum class CardinalDirection {
    kSouth, kNorth, kEast, kWest, kUp, kDown
  };

  auto allocate_quad = [&](int x, int y, int z, CardinalDirection dir) {
    const size_t kVertexOffset = num_allocated_quads * kQuadSizeVertices;

    switch (dir) {
      case CardinalDirection::kSouth:
        vertices[kVertexOffset  + 0] = 1.0f + x; vertices[kVertexOffset  + 1] = 1.0f + y; vertices[kVertexOffset  + 2] = 1.0f + z;
        vertices[kVertexOffset  + 5] = 1.0f + x; vertices[kVertexOffset  + 6] = 0.0f + y; vertices[kVertexOffset  + 7] = 1.0f + z;
        vertices[kVertexOffset + 10] = 0.0f + x; vertices[kVertexOffset + 11] = 0.0f + y; vertices[kVertexOffset + 12] = 1.0f + z;
        vertices[kVertexOffset + 15] = 0.0f + x; vertices[kVertexOffset + 16] = 1.0f + y; vertices[kVertexOffset + 17] = 1.0f + z;
        break;

      case CardinalDirection::kNorth:
        vertices[kVertexOffset  + 0] = 0.0f + x; vertices[kVertexOffset  + 1] = 1.0f + y; vertices[kVertexOffset  + 2] = 0.0f + z;
        vertices[kVertexOffset  + 5] = 0.0f + x; vertices[kVertexOffset  + 6] = 0.0f + y; vertices[kVertexOffset  + 7] = 0.0f + z;
        vertices[kVertexOffset + 10] = 1.0f + x; vertices[kVertexOffset + 11] = 0.0f + y; vertices[kVertexOffset + 12] = 0.0f + z;
        vertices[kVertexOffset + 15] = 1.0f + x; vertices[kVertexOffset + 16] = 1.0f + y; vertices[kVertexOffset + 17] = 0.0f + z;
        break;

      case CardinalDirection::kEast:
        vertices[kVertexOffset  + 0] = 1.0f + x; vertices[kVertexOffset  + 1] = 1.0f + y; vertices[kVertexOffset  + 2] = 0.0f + z;
        vertices[kVertexOffset  + 5] = 1.0f + x; vertices[kVertexOffset  + 6] = 0.0f + y; vertices[kVertexOffset  + 7] = 0.0f + z;
        vertices[kVertexOffset + 10] = 1.0f + x; vertices[kVertexOffset + 11] = 0.0f + y; vertices[kVertexOffset + 12] = 1.0f + z;
        vertices[kVertexOffset + 15] = 1.0f + x; vertices[kVertexOffset + 16] = 1.0f + y; vertices[kVertexOffset + 17] = 1.0f + z;
        break;

      case CardinalDirection::kWest:
        vertices[kVertexOffset  + 0] = 0.0f + x; vertices[kVertexOffset  + 1] = 1.0f + y; vertices[kVertexOffset  + 2] = 1.0f + z;
        vertices[kVertexOffset  + 5] = 0.0f + x; vertices[kVertexOffset  + 6] = 0.0f + y; vertices[kVertexOffset  + 7] = 1.0f + z;
        vertices[kVertexOffset + 10] = 0.0f + x; vertices[kVertexOffset + 11] = 0.0f + y; vertices[kVertexOffset + 12] = 0.0f + z;
        vertices[kVertexOffset + 15] = 0.0f + x; vertices[kVertexOffset + 16] = 1.0f + y; vertices[kVertexOffset + 17] = 0.0f + z;
        break;

      case CardinalDirection::kDown:
        vertices[kVertexOffset  + 0] = 1.0f + x; vertices[kVertexOffset  + 1] = 0.0f + y; vertices[kVertexOffset  + 2] = 1.0f + z;
        vertices[kVertexOffset  + 5] = 1.0f + x; vertices[kVertexOffset  + 6] = 0.0f + y; vertices[kVertexOffset  + 7] = 0.0f + z;
        vertices[kVertexOffset + 10] = 0.0f + x; vertices[kVertexOffset + 11] = 0.0f + y; vertices[kVertexOffset + 12] = 0.0f + z;
        vertices[kVertexOffset + 15] = 0.0f + x; vertices[kVertexOffset + 16] = 0.0f + y; vertices[kVertexOffset + 17] = 1.0f + z;
        break;

      case CardinalDirection::kUp:
        vertices[kVertexOffset  + 0] = 1.0f + x; vertices[kVertexOffset  + 1] = 1.0f + y; vertices[kVertexOffset  + 2] = 0.0f + z;
        vertices[kVertexOffset  + 5] = 1.0f + x; vertices[kVertexOffset  + 6] = 1.0f + y; vertices[kVertexOffset  + 7] = 1.0f + z;
        vertices[kVertexOffset + 10] = 0.0f + x; vertices[kVertexOffset + 11] = 1.0f + y; vertices[kVertexOffset + 12] = 1.0f + z;
        vertices[kVertexOffset + 15] = 0.0f + x; vertices[kVertexOffset + 16] = 1.0f + y; vertices[kVertexOffset + 17] = 0.0f + z;
        break;
    }

    allocate_quad_uvs(kVertexOffset);
    allocate_quad_indices();
  };

  for (int x = 0; x < kChunkWidth; ++x) {
    for (int y = 0; y < kChunkHeight; ++y) {
      for (int z = 0; z < kChunkDepth; ++z) {

        allocate_quad(x, y, z, CardinalDirection::kSouth);
        allocate_quad(x, y, z, CardinalDirection::kNorth);
        allocate_quad(x, y, z, CardinalDirection::kEast);
        allocate_quad(x, y, z, CardinalDirection::kWest);
        allocate_quad(x, y, z, CardinalDirection::kUp);
        allocate_quad(x, y, z, CardinalDirection::kDown);

      }
    }
  }

  return new VertexArray(vertices.data(), vertices.size(), indices.data(), indices.size());
}
