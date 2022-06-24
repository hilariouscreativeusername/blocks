#pragma once

#include "block.h"
#include "graphics/vertex_array.h"

VertexArray* GenerateChunkMesh(Block* blocks, int chunkx, int chunky, int chunkz);
