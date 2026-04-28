// sensors.cpp
#include "sensors.h"
#include "config.h"
#include <Arduino.h>

void sensorsInit() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

float readDistanceInches() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  long duration = pulseIn(ECHO_PIN, HIGH, 30000);
  if (duration == 0) return -1;
  return duration * 0.0133 / 2;
}

float averageDistance(int samples) {
  float total = 0;
  int valid = 0;
  for (int i = 0; i < samples; i++) {
    float d = readDistanceInches();
    if (d > 0) { total += d; valid++; }
    delay(50);
  }
  return valid > 0 ? total / valid : -1;
}