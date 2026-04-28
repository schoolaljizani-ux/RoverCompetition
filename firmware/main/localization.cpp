// localization.cpp
#include "localization.h"
#include "config.h"
#include "grid.h"
#include "sensors.h"
#include <Arduino.h>

static int rover_row;
static int rover_col;
static int rover_heading;

void localizationInit() {
  rover_row = START_ROW;
  rover_col = START_COL;
  rover_heading = START_HEADING;
}

int getRow()     { return rover_row; }
int getCol()     { return rover_col; }
int getHeading() { return rover_heading; }

static void headingDelta(int heading, int& dr, int& dc) {
  switch (heading) {
    case HEADING_NORTH: dr = -1; dc =  0; break;
    case HEADING_EAST:  dr =  0; dc =  1; break;
    case HEADING_SOUTH: dr =  1; dc =  0; break;
    case HEADING_WEST:  dr =  0; dc = -1; break;
  }
}

float expectedWallDistance() {
  int dr, dc;
  headingDelta(rover_heading, dr, dc);
  int r = rover_row + dr;
  int c = rover_col + dc;
  int cells = 0;
  while (!isObstacle(r, c)) {
    cells++;
    r += dr;
    c += dc;
    if (cells > 50) break;  // safety
  }
  return cells * CELL_INCHES;
}

void updatePositionAfterMove(int cells) {
  int dr, dc;
  headingDelta(rover_heading, dr, dc);
  rover_row += dr * cells;
  rover_col += dc * cells;
}

void updateHeadingAfterTurn(bool clockwise) {
  if (clockwise) rover_heading = (rover_heading + 1) % 4;
  else           rover_heading = (rover_heading + 3) % 4;
}

bool localize() {
  float expected = expectedWallDistance();
  float measured = averageDistance(5);
  if (measured < 0 || measured > ULTRASONIC_MAX_INCHES) return false;
  if (expected > ULTRASONIC_MAX_INCHES) return false;

  float error_inches = expected - measured;
  int error_cells = (int)round(error_inches / CELL_INCHES);

  if (error_cells != 0) {
    // Position estimate was off; rover is closer/farther than expected
    int dr, dc;
    headingDelta(rover_heading, dr, dc);
    rover_row += dr * error_cells;
    rover_col += dc * error_cells;
    return true;
  }
  return false;
}