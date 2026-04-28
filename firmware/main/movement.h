// movement.h
#ifndef MOVEMENT_H
#define MOVEMENT_H

void movementInit();
void driveForward();
void driveBackward();
void strafeLeft();
void strafeRight();
void turnClockwise();
void turnCounterclockwise();
void stopMoving();

void moveCellsForward(int cells);
void turn90Right();
void turn90Left();
void turn180();

#endif