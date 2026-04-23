// Arm initialization at neutral position.
// Attaches servos one at a time and immediately writes the neutral angle
// to prevent the arm from snapping to a garbage value on boot.
//
// Neutral positions:
//   Gripper: 44
//   Wrist:   88
//   Elbow:   180
//   Shoulder: 138
//   Base:    128
//
// The jog utility (commented below) was used to find these values.
// Attach one joint, use W/S to adjust angle, N to confirm and move to next.

// Jog utility (uncomment to find neutral positions for a different arm):
//
// #include <ESP32Servo.h>
// Servo base, shoulder, elbow, wrist, gripper;
// Servo* joints[] = {&gripper, &wrist, &elbow, &shoulder, &base};
// int pins[]       = {4, 33, 27, 26, 25};
// String names[]   = {"Gripper", "Wrist", "Elbow", "Shoulder", "Base"};
// int angles[]     = {90, 90, 90, 90, 90};
// int current      = 0;
// void setup() {
//   Serial.begin(115200);
//   joints[0]->attach(pins[0]);
//   joints[0]->write(angles[0]);
//   Serial.println("W=up  S=down  N=attach next joint");
//   Serial.print("Current: "); Serial.println(names[current]);
// }
// void loop() {
//   if (Serial.available()) {
//     char cmd = tolower(Serial.read());
//     if (cmd == 'w') {
//       angles[current] = constrain(angles[current] + 2, 0, 180);
//       joints[current]->write(angles[current]);
//       Serial.print(names[current]); Serial.print(": "); Serial.println(angles[current]);
//     }
//     if (cmd == 's') {
//       angles[current] = constrain(angles[current] - 2, 0, 180);
//       joints[current]->write(angles[current]);
//       Serial.print(names[current]); Serial.print(": "); Serial.println(angles[current]);
//     }
//     if (cmd == 'n') {
//       Serial.print(names[current]); Serial.print(" saved at: "); Serial.println(angles[current]);
//       current++;
//       if (current >= 5) {
//         Serial.println("All joints attached.");
//         return;
//       }
//       joints[current]->attach(pins[current]);
//       joints[current]->write(angles[current]);
//       Serial.print("Current: "); Serial.println(names[current]);
//     }
//   }
// }

#include <ESP32Servo.h>

Servo base, shoulder, elbow, wrist, gripper;

void slowMove(Servo &s, int from, int target, int stepDelay = 15) {
  if (from < target) {
    for (int p = from; p <= target; p++) { s.write(p); delay(stepDelay); }
  } else {
    for (int p = from; p >= target; p--) { s.write(p); delay(stepDelay); }
  }
}

void setup() {
  Serial.begin(115200);
  gripper.attach(4);   gripper.write(44);   delay(500);
  wrist.attach(33);    wrist.write(88);     delay(500);
  elbow.attach(27);    elbow.write(180);    delay(500);
  shoulder.attach(26); shoulder.write(138); delay(500);
  base.attach(25);     base.write(128);     delay(500);
  Serial.println("All joints at neutral.");
}

void loop() {}
