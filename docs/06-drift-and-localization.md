# 06 - Drift Fix and Localization Refactor

## The Drift

Rover kept curving left. Tried the obvious stuff first.

Lifted it, ran forward. All four wheels spinning the same speed. Swapped front-left and front-right motor wires. Drift stayed left. Retightened wheel screws, realigned wheels. Still drifted left.

Looked at the mecanum pattern from underneath. Top rollers form an X pointing inward when you flip the bottom view to top-down. Pattern was correct.

Concluded it was load-related, not mechanical. Lifted the rover, no drift. On the ground, drift.

## Bypassing the Library

The vehicle library only exposes `Move(dir, speed)` which sets both PWM channels to the same value. Looked at the .cpp:

```cpp
void vehicle::Move(int Dir, int Speed) {
  digitalWrite(EN_PIN, LOW);
  analogWrite(PWM1_PIN, Speed);
  analogWrite(PWM2_PIN, Speed);
  ...
}
```

Both PWMs locked together. No way to trim one side from inside the library.

Wrote my own version that takes two speeds:

```cpp
void moveForwardTrimmed(int rightSpeed, int leftSpeed) {
  digitalWrite(EN_PIN, LOW);
  analogWrite(PWM1_PIN, rightSpeed);
  analogWrite(PWM2_PIN, leftSpeed);
  digitalWrite(STCP_PIN, LOW);
  shiftOut(DATA_PIN, SHCP_PIN, MSBFIRST, Forward);
  digitalWrite(STCP_PIN, HIGH);
}
```

Tested which PWM controlled which side by setting one to 0 and watching which wheels spun. PWM1 = right, PWM2 = left.

## Trim Values

Drift was left, so right side was pushing harder. Trimmed right down.

Right 140, left 150. No more drift.

## Recalibrating Forward Time

Old calibration was 107 ms/inch at speed 150 both sides. With the trim, right side is slower so the average changes.

Re-ran the ultrasonic forward test with the trimmed function. New value: 120 ms/inch, 1018 ms per cell.

## Turn Calibration

Spun the rover clockwise for 5000 ms with a tape mark on the floor. Counted 400 degrees of rotation.

Math: 5000 / 400 = 12.5 ms per degree. 90 degrees = 1125 ms.

Tested. Undershoots by ~7 degrees. Bumped to 1300. Still slightly under but close enough.

180 degrees = 2600 ms. Bumped to 2750 to cover undershoot variance.

## Closed-Loop Forward

Time-based moves drift over a 15 minute demo as the battery drains. Need correction.

Wrote a closed-loop version: drive forward, ping ultrasonic continuously, stop when reading is at or below target distance.

```cpp
moveForwardTrimmed(...);
while (true) {
  float d = readDistanceInches();
  if (d > 0 && d <= STOP_DISTANCE) break;
  delay(30);
}
stopMoving();
```

Works as long as something is in front of the rover within ultrasonic range (~157 inches max).

## Modular Refactor

Single .ino file was getting big. Split into:
main/
├── main.ino
├── config.h           pins, speeds, calibration constants
├── grid.h/.cpp        obstacle blocks, isObstacle()
├── sensors.h/.cpp     ultrasonic
├── movement.h/.cpp    trimmed drive, turn, stop
├── arm.h/.cpp         servo init, neutral
└── localization.h/.cpp ray-cast, position correction

All flat in the sketch folder so the Arduino IDE picks them up.

## Obstacle Blocks Instead of a Grid Array

Could store the room as a 41x45 byte array (1.8 KB). Or store it as a list of rectangles since every static obstacle is rectangular.

Five blocks describe the whole room: front wall, left counter, right counter, back counter, teacher's desk.

```cpp
const Block obstacles[] = {
  {0,  0,  0,  44},
  {0,  0,  40, 2},
  {0,  42, 40, 44},
  {36, 0,  38, 44},
  {5,  14, 7,  29},
};
```

50 bytes vs 1.8 KB. `isObstacle(r, c)` checks against the list. Easier to edit when reality doesnt match the map.

Tables stay out of the list. The rover passes underneath them.

## Localization

Rover knows its row, col, and heading. After each move it can ping the ultrasonic and compare what it reads to what it should see if it were exactly where it thinks it is.

Ray-cast from current cell in the heading direction, count cells until you hit an obstacle, multiply by 8.5 inches.

If expected is 100 inches but ultrasonic reads 92, rover is 8 inches further than it thought. Correct the position estimate.

Software-only correction for now. Doesn't physically nudge the rover, just updates the row/col it thinks it's at.

## Where I Am

Forward drive trimmed and calibrated. Closed-loop forward works. Turn calibrated. Refactor done. Localization scaffolding in place.

Next: A* on the ESP32 itself, comms with the WROVER, mission orchestration.
