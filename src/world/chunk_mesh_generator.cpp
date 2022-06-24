#include "chunk_mesh_generator.h"

#include <vector>

#include <glm/glm.hpp>

#include "chunk.h"

VertexArray* GenerateMesh(Block* blocks, int chunkx, int chunky, int chunkz) {
  const int kChunkXOffs = chunkx * kChunkWidth;
  const int kChunkYOffs = chunky * kChunkHeight;
  const int kChunkZOffs = chunkz * kChunkDepth;

  // All sizes in floats
  constexpr size_t kVertexSize         = 6;
  constexpr size_t kUniqueQuadVertices = 4;
  constexpr size_t kQuadSizeVertices   = kUniqueQuadVertices * kVertexSize;
  constexpr size_t kMaxBlockVertices   = kQuadSizeVertices * 6;
  constexpr size_t kChunkSize          = kChunkWidth * kChunkHeight * kChunkDepth;
  constexpr size_t kMaxVertices        = kChunkSize * kMaxBlockVertices;
  std::vector<float> vertices(kMaxVertices);

  // Size in unsigned ints
  constexpr size_t kQuadSizeIndices = 6;
  constexpr size_t kBlockMaxQuads   = 6;
  constexpr size_t kMaxIndices = kChunkSize * kQuadSizeIndices * kBlockMaxQuads;
  std::vector<unsigned int> indices(kMaxIndices);

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

  auto allocate_quad_uvs = [&](size_t vertex_offset, Block block, CardinalDirection dir){
    float w = BlockProps::BlockTextureIndex(block, dir);
  
    vertices[vertex_offset  + 3] = 1.0f;
    vertices[vertex_offset  + 4] = 0.0f;
    vertices[vertex_offset  + 5] = w;
    vertices[vertex_offset  + 9] = 1.0f;
    vertices[vertex_offset + 10] = 1.0f;
    vertices[vertex_offset + 11] = w;
    vertices[vertex_offset + 15] = 0.0f;
    vertices[vertex_offset + 16] = 1.0f;
    vertices[vertex_offset + 17] = w;
    vertices[vertex_offset + 21] = 0.0f;
    vertices[vertex_offset + 22] = 0.0f;
    vertices[vertex_offset + 23] = w;
  };

  auto is_quad_occluded = [&](int x, int y, int z, CardinalDirection dir) {
    switch (dir) {
      case CardinalDirection::kSouth:
        if (z == kChunkDepth - 1) {
          return false; // TODO: Check adjacent chunks
        }
        else {
          return BlockProps::IsOccluding(blocks[x + y * kChunkHeight + (z + 1) * kChunkHeight * kChunkDepth]);
        }

      case CardinalDirection::kNorth:
        if (z == 0) {
          return false; // TODO: Check adjacent chunks
        }
        else {
          return BlockProps::IsOccluding(blocks[x + y * kChunkHeight + (z - 1) * kChunkHeight * kChunkDepth]);
        }

      case CardinalDirection::kEast:
        if (x == kChunkWidth - 1) {
          return false; // TODO: Check adjacent chunks
        }
        else {
          return BlockProps::IsOccluding(blocks[(x + 1) + y * kChunkHeight + z * kChunkHeight * kChunkDepth]);
        }

      case CardinalDirection::kWest:
        if (x == 0) {
          return false; // TODO: Check adjacent chunks
        }
        else {
          return BlockProps::IsOccluding(blocks[(x - 1) + y * kChunkHeight + z * kChunkHeight * kChunkDepth]);
        }

      case CardinalDirection::kUp:
        if (y == kChunkHeight - 1) {
          return false; // TODO: Check adjacent chunks
        }
        else {
          return BlockProps::IsOccluding(blocks[x + (y + 1) * kChunkHeight + z * kChunkHeight * kChunkDepth]);
        }

      case CardinalDirection::kDown:
        if (y == 0) {
          return false; // TODO: Check adjacent chunks
        }
        else {
          return BlockProps::IsOccluding(blocks[x + (y - 1) * kChunkHeight + z * kChunkHeight * kChunkDepth]);
        }
    }
  };

  auto allocate_quad = [&](int x, int y, int z, CardinalDirection dir) {
    if (is_quad_occluded(x, y, z, dir)) {
      return;
    }

    const size_t kVertexOffset = num_allocated_quads * kQuadSizeVertices;

    switch (dir) {
      case CardinalDirection::kSouth:
        vertices[kVertexOffset  + 0] = 1.0f + x + kChunkXOffs; vertices[kVertexOffset  + 1] = 1.0f + y + kChunkYOffs; vertices[kVertexOffset  + 2] = 1.0f + z + kChunkZOffs;
        vertices[kVertexOffset  + 6] = 1.0f + x + kChunkXOffs; vertices[kVertexOffset  + 7] = 0.0f + y + kChunkYOffs; vertices[kVertexOffset  + 8] = 1.0f + z + kChunkZOffs;
        vertices[kVertexOffset + 12] = 0.0f + x + kChunkXOffs; vertices[kVertexOffset + 13] = 0.0f + y + kChunkYOffs; vertices[kVertexOffset + 14] = 1.0f + z + kChunkZOffs;
        vertices[kVertexOffset + 18] = 0.0f + x + kChunkXOffs; vertices[kVertexOffset + 19] = 1.0f + y + kChunkYOffs; vertices[kVertexOffset + 20] = 1.0f + z + kChunkZOffs;
        break;

      case CardinalDirection::kNorth:
        vertices[kVertexOffset  + 0] = 0.0f + x + kChunkXOffs; vertices[kVertexOffset  + 1] = 1.0f + y + kChunkYOffs; vertices[kVertexOffset  + 2] = 0.0f + z + kChunkZOffs;
        vertices[kVertexOffset  + 6] = 0.0f + x + kChunkXOffs; vertices[kVertexOffset  + 7] = 0.0f + y + kChunkYOffs; vertices[kVertexOffset  + 8] = 0.0f + z + kChunkZOffs;
        vertices[kVertexOffset + 12] = 1.0f + x + kChunkXOffs; vertices[kVertexOffset + 13] = 0.0f + y + kChunkYOffs; vertices[kVertexOffset + 14] = 0.0f + z + kChunkZOffs;
        vertices[kVertexOffset + 18] = 1.0f + x + kChunkXOffs; vertices[kVertexOffset + 19] = 1.0f + y + kChunkYOffs; vertices[kVertexOffset + 20] = 0.0f + z + kChunkZOffs;
        break;

      case CardinalDirection::kEast:
        vertices[kVertexOffset  + 0] = 1.0f + x + kChunkXOffs; vertices[kVertexOffset  + 1] = 1.0f + y + kChunkYOffs; vertices[kVertexOffset  + 2] = 0.0f + z + kChunkZOffs;
        vertices[kVertexOffset  + 6] = 1.0f + x + kChunkXOffs; vertices[kVertexOffset  + 7] = 0.0f + y + kChunkYOffs; vertices[kVertexOffset  + 8] = 0.0f + z + kChunkZOffs;
        vertices[kVertexOffset + 12] = 1.0f + x + kChunkXOffs; vertices[kVertexOffset + 13] = 0.0f + y + kChunkYOffs; vertices[kVertexOffset + 14] = 1.0f + z + kChunkZOffs;
        vertices[kVertexOffset + 18] = 1.0f + x + kChunkXOffs; vertices[kVertexOffset + 19] = 1.0f + y + kChunkYOffs; vertices[kVertexOffset + 20] = 1.0f + z + kChunkZOffs;
        break;

      case CardinalDirection::kWest:
        vertices[kVertexOffset  + 0] = 0.0f + x + kChunkXOffs; vertices[kVertexOffset  + 1] = 1.0f + y + kChunkYOffs; vertices[kVertexOffset  + 2] = 1.0f + z + kChunkZOffs;
        vertices[kVertexOffset  + 6] = 0.0f + x + kChunkXOffs; vertices[kVertexOffset  + 7] = 0.0f + y + kChunkYOffs; vertices[kVertexOffset  + 8] = 1.0f + z + kChunkZOffs;
        vertices[kVertexOffset + 12] = 0.0f + x + kChunkXOffs; vertices[kVertexOffset + 13] = 0.0f + y + kChunkYOffs; vertices[kVertexOffset + 14] = 0.0f + z + kChunkZOffs;
        vertices[kVertexOffset + 18] = 0.0f + x + kChunkXOffs; vertices[kVertexOffset + 19] = 1.0f + y + kChunkYOffs; vertices[kVertexOffset + 20] = 0.0f + z + kChunkZOffs;
        break;

      case CardinalDirection::kDown:
        vertices[kVertexOffset  + 0] = 1.0f + x + kChunkXOffs; vertices[kVertexOffset  + 1] = 0.0f + y + kChunkYOffs; vertices[kVertexOffset  + 2] = 1.0f + z + kChunkZOffs;
        vertices[kVertexOffset  + 6] = 1.0f + x + kChunkXOffs; vertices[kVertexOffset  + 7] = 0.0f + y + kChunkYOffs; vertices[kVertexOffset  + 8] = 0.0f + z + kChunkZOffs;
        vertices[kVertexOffset + 12] = 0.0f + x + kChunkXOffs; vertices[kVertexOffset + 13] = 0.0f + y + kChunkYOffs; vertices[kVertexOffset + 14] = 0.0f + z + kChunkZOffs;
        vertices[kVertexOffset + 18] = 0.0f + x + kChunkXOffs; vertices[kVertexOffset + 19] = 0.0f + y + kChunkYOffs; vertices[kVertexOffset + 20] = 1.0f + z + kChunkZOffs;
        break;

      case CardinalDirection::kUp:
        vertices[kVertexOffset  + 0] = 1.0f + x + kChunkXOffs; vertices[kVertexOffset  + 1] = 1.0f + y + kChunkYOffs; vertices[kVertexOffset  + 2] = 0.0f + z + kChunkZOffs;
        vertices[kVertexOffset  + 6] = 1.0f + x + kChunkXOffs; vertices[kVertexOffset  + 7] = 1.0f + y + kChunkYOffs; vertices[kVertexOffset  + 8] = 1.0f + z + kChunkZOffs;
        vertices[kVertexOffset + 12] = 0.0f + x + kChunkXOffs; vertices[kVertexOffset + 13] = 1.0f + y + kChunkYOffs; vertices[kVertexOffset + 14] = 1.0f + z + kChunkZOffs;
        vertices[kVertexOffset + 18] = 0.0f + x + kChunkXOffs; vertices[kVertexOffset + 19] = 1.0f + y + kChunkYOffs; vertices[kVertexOffset + 20] = 0.0f + z + kChunkZOffs;
        break;
    }

    Block block = blocks[x + y * kChunkHeight + z * kChunkHeight * kChunkDepth];
    allocate_quad_uvs(kVertexOffset, block, dir);
    allocate_quad_indices();
  };

  for (int x = 0; x < kChunkWidth; ++x) {
    for (int y = 0; y < kChunkHeight; ++y) {
      for (int z = 0; z < kChunkDepth; ++z) {
        Block block = blocks[x + y * kChunkHeight + z * kChunkHeight * kChunkDepth];
        if (block == Block::kAir) {
          continue;
        }

        allocate_quad(x, y, z, CardinalDirection::kSouth);
        allocate_quad(x, y, z, CardinalDirection::kNorth);
        allocate_quad(x, y, z, CardinalDirection::kEast);
        allocate_quad(x, y, z, CardinalDirection::kWest);
        allocate_quad(x, y, z, CardinalDirection::kUp);
        allocate_quad(x, y, z, CardinalDirection::kDown);

      }
    }
  }

  const size_t kVertexOffset = num_allocated_quads * kQuadSizeVertices;
  vertices.resize(kVertexOffset);
  const size_t kIndexOffset = num_allocated_quads * kQuadSizeIndices;
  indices.resize(kIndexOffset);

  return new VertexArray(vertices.data(), vertices.size(), indices.data(), indices.size());
}
