#pragma once

#include <tuple>
#include <vector>

#include <glm/vec3.hpp>

struct ClientData {
  bool IsChunkLoaded(int x, int y, int z) {
    for (auto& chunk : loaded_chunks_) {
      if (chunk.x == x && chunk.y == y && chunk.z == z) {
        return true;
      }
    }
    return false;
  }

  void FlagChunkLoaded(int x, int y, int z) {
    loaded_chunks_.push_back({ x, y, z });
  }

  int player_x_, player_y_, player_z_;
  std::vector<glm::ivec3> loaded_chunks_;
};
