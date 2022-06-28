#include "chunk_generator.h"

#include "chunk.h"

#include <ctime>
#include <random>

namespace ChunkGenerator {

void SRand() {
  srand(time(0));
}

Block* GenerateChunk(int chunkx, int chunky, int chunkz) {
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
