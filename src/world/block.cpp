#include "block.h"

namespace BlockProps {

bool IsOccluding(Block block) {
  return block != Block::kAir && block != Block::kLeaves;
}

float BlockTextureIndex(Block block, CardinalDirection dir) {
  switch (block) {
    case Block::kDirt:
      return 2.0f;
    
    case Block::kBasalt:
      return 1.0f;
      
    case Block::kLeaves:
      return 6.0f;
      
    case Block::kLog:
      if (dir == CardinalDirection::kUp || dir == CardinalDirection::kDown) {
        return 12.0f;
      }
      else {
        return 11.0f;
      }
  
    default:
      return 0.0f;
  }
}

}
