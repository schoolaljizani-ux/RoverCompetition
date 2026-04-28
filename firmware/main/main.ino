// main.ino
#include "config.h"
#include "arm.h"
#include "movement.h"
#include "sensors.h"
#include "localization.h"
#include "grid.h"

void setup() {
  Serial.begin(115200);
  delay(500);

  Serial.println("Rover boot");

  movementInit();
  armInit();
  sensorsInit();
  localizationInit();

  Serial.print("Start: row="); Serial.print(getRow());
  Serial.print(" col="); Serial.print(getCol());
  Serial.print(" heading="); Serial.println(getHeading());

  delay(3000);

  // Test: drive forward toward desk, stop at 12 inches, turn 180
  Serial.println("Driving forward, watching for desk...");
  driveForward();

  while (true) {
    float d = readDistanceInches();
    if (d > 0 && d <= 12.0) {
      Serial.print("Stopped at "); Serial.print(d); Serial.println(" in");
      break;
    }
    delay(30);
  }
  stopMoving();
  delay(500);

  // Try to localize against the wall we just hit
  if (localize()) {
    Serial.println("Position corrected");
    Serial.print("Now at: row="); Serial.print(getRow());
    Serial.print(" col="); Serial.println(getCol());
  }

  delay(500);

  Serial.println("Turning 180");
  turn180();
  updateHeadingAfterTurn(true);
  updateHeadingAfterTurn(true);

  Serial.println("Done");
}

void loop() {}