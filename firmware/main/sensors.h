// sensors.h
#ifndef SENSORS_H
#define SENSORS_H

void sensorsInit();
float readDistanceInches();
float averageDistance(int samples = 5);

#endif