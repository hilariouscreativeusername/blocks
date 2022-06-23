#pragma once

enum class Block : unsigned char {
  kAir    = 0,
  kDirt   = 1,
  kStone  = 2,
  kLog    = 3,
  kLeaves = 4,
};

namespace BlockProps {

bool IsOccluding(Block block);

}
