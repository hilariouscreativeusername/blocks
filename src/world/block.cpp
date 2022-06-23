#include "block.h"

namespace BlockProps {

bool IsOccluding(Block block) {
  return block != Block::kAir && block != Block::kLeaves;
}

}
