// Movement calibration sketch.
// Hardcoded sequence: runs a single directional move on boot after a 5s delay.
// Unplug USB, place rover on ground, press reset, measure with a ruler.
//
// Results (at speed 150):
//   Forward 1000ms = 10 inches
//   So: 100 ms per inch
//   One cell (8.5") forward = 850 ms

#include <ESP32Servo.h>
#include <vehicle.h>

vehicle myCar;
Servo base, shoulder, elbow, wrist, gripper;

int MOVE_SPEED = 150;
int TEST_TIME  = 1000;

void setupArm() {
  gripper.attach(4);   gripper.write(44);   delay(500);
  wrist.attach(33);    wrist.write(88);     delay(500);
  elbow.attach(27);    elbow.write(180);    delay(500);
  shoulder.attach(26); shoulder.write(138); delay(500);
  base.attach(25);     base.write(128);     delay(500);
}

void setup() {
  Serial.begin(115200);
  myCar.Init();
  setupArm();

  Serial.println("Starting in 5 seconds...");
  delay(5000);

  Serial.println("Moving forward");
  myCar.Move(Forward, MOVE_SPEED);
  delay(TEST_TIME);
  myCar.Move(Stop, 0);
  Serial.println("Done");
}

void loop() {}
