// grid.cpp
#include "grid.h"
#include "config.h"

const Block obstacles[] = {
  {0,  0,  0,  44},   // front wall
  {0,  0,  40, 2},    // left counter
  {0,  42, 40, 44},   // right counter
  {36, 0,  38, 44},   // back counter
  {5,  14, 7,  29},   // teacher's desk
};

const int NUM_OBSTACLES = sizeof(obstacles) / sizeof(obstacles[0]);

bool isObstacle(int r, int c) {
  if (r < 0 || r >= GRID_ROWS || c < 0 || c >= GRID_COLS) return true;
  for (int i = 0; i < NUM_OBSTACLES; i++) {
    const Block& o = obstacles[i];
    if (r >= o.r1 && r <= o.r2 && c >= o.c1 && c <= o.c2) return true;
  }
  return false;
}