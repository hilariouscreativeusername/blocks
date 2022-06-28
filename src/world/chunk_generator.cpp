#include "chunk_generator.h"

#include "chunk.h"

#include <random>

namespace ChunkGenerator {

Block* GenerateChunk(int chunkx, int chunky, int chunkz) {
  srand(7919 + chunkx * 5903 + chunky * 4027 + chunkz * 3119);

  Block* blocks = new Block[kChunkWidth * kChunkHeight * kChunkDepth];

  for (size_t x = 0; x < kChunkWidth; ++x) {
    for (size_t y = 0; y < kChunkHeight; ++y) {
      for (size_t z = 0; z < kChunkDepth; ++z) {
        blocks[x + y * kChunkHeight + z * kChunkHeight * kChunkDepth] = rand() % 2 == 0 ? Block::kLog : Block::kLeaves;
      }
    }
  }

  return blocks;
}

}
