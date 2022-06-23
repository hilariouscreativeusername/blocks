#pragma once

enum class Block : unsigned char {
  kAir    = 0,
  kDirt   = 1,
  kBasalt = 2,
  kLog    = 3,
  kLeaves = 4,
};

// South = +Z,  North = -Z
// East  = +X,  West  = -X
// Down  = -Y,  Up    = +Y
enum class CardinalDirection {
  kSouth, kNorth, kEast, kWest, kUp, kDown
};

namespace BlockProps {

bool IsOccluding(Block block);
float BlockTextureIndex(Block block, CardinalDirection dir);

}
