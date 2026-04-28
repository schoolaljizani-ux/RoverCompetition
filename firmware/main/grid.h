// grid.h
#ifndef GRID_H
#define GRID_H

struct Block {
  int r1, c1, r2, c2;
};

bool isObstacle(int r, int c);

#endif