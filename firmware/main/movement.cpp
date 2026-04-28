#include "movement.h"
#include "config.h"
#include <Arduino.h>
#include <vehicle.h>

static vehicle myCar;

void movementInit() {
  myCar.Init();
}

static void driveTrimmed(int dir) {
  digitalWrite(EN_PIN, LOW);
  analogWrite(PWM1_PIN, RIGHT_SPEED);
  analogWrite(PWM2_PIN, LEFT_SPEED);
  digitalWrite(STCP_PIN, LOW);
  shiftOut(DATA_PIN, SHCP_PIN, MSBFIRST, dir);
  digitalWrite(STCP_PIN, HIGH);
}

static void driveTrimmedKick(int dir) {
  digitalWrite(EN_PIN, LOW);
  analogWrite(PWM1_PIN, 200);
  analogWrite(PWM2_PIN, 200);
  digitalWrite(STCP_PIN, LOW);
  shiftOut(DATA_PIN, SHCP_PIN, MSBFIRST, dir);
  digitalWrite(STCP_PIN, HIGH);
  delay(100);
  analogWrite(PWM1_PIN, RIGHT_SPEED);
  analogWrite(PWM2_PIN, LEFT_SPEED);
}

void driveForward()          { driveTrimmedKick(Forward); }
void driveBackward()         { driveTrimmed(Backward); }
void strafeLeft()            { driveTrimmed(Move_Left); }
void strafeRight()           { driveTrimmed(Move_Right); }
void turnClockwise()         { driveTrimmed(Clockwise); }
void turnCounterclockwise()  { driveTrimmed(Contrarotate); }

void stopMoving() {
  myCar.Move(Stop, 0);
}

void moveCellsForward(int cells) {
  driveForward();
  delay(cells * MS_PER_CELL);
  stopMoving();
}

void turn90Right() {
  turnClockwise();
  delay(TURN_90);
  stopMoving();
}

void turn90Left() {
  turnCounterclockwise();
  delay(TURN_90);
  stopMoving();
}

void turn180() {
  turnClockwise();
  delay(TURN_180);
  stopMoving();
}