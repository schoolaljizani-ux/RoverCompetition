// arm.cpp
#include "arm.h"
#include "config.h"
#include <Arduino.h>
#include <ESP32Servo.h>

static Servo base, shoulder, elbow, wrist, gripper;

void armInit() {
  gripper.attach(ARM_GRIPPER_PIN);   gripper.write(ARM_GRIPPER_NEUTRAL);   delay(500);
  wrist.attach(ARM_WRIST_PIN);       wrist.write(ARM_WRIST_NEUTRAL);       delay(500);
  elbow.attach(ARM_ELBOW_PIN);       elbow.write(ARM_ELBOW_NEUTRAL);       delay(500);
  shoulder.attach(ARM_SHOULDER_PIN); shoulder.write(ARM_SHOULDER_NEUTRAL); delay(500);
  base.attach(ARM_BASE_PIN);         base.write(ARM_BASE_NEUTRAL);         delay(500);
}

void armNeutral() {
  gripper.write(ARM_GRIPPER_NEUTRAL);
  wrist.write(ARM_WRIST_NEUTRAL);
  elbow.write(ARM_ELBOW_NEUTRAL);
  shoulder.write(ARM_SHOULDER_NEUTRAL);
  base.write(ARM_BASE_NEUTRAL);
}

void armRaw(int b, int s, int e, int w, int g) {
  // helper for later when you add poses
  base.write(b);
  shoulder.write(s);
  elbow.write(e);
  wrist.write(w);
  gripper.write(g);
}