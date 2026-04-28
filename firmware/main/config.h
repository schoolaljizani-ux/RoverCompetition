#ifndef CONFIG_H
#define CONFIG_H

// Arm servo pins
#define ARM_BASE_PIN     25
#define ARM_SHOULDER_PIN 26
#define ARM_ELBOW_PIN    27
#define ARM_WRIST_PIN    33
#define ARM_GRIPPER_PIN  4

// Arm neutral positions
#define ARM_BASE_NEUTRAL     128
#define ARM_SHOULDER_NEUTRAL 138
#define ARM_ELBOW_NEUTRAL    180
#define ARM_WRIST_NEUTRAL    88
#define ARM_GRIPPER_NEUTRAL  44

// Ultrasonic pins
#define TRIG_PIN 13
#define ECHO_PIN 14

// Movement calibration
#define RIGHT_SPEED 140
#define LEFT_SPEED  150
#define MS_PER_INCH 120
#define CELL_INCHES 8.5
#define MS_PER_CELL 1018
#define TURN_90     1300
#define TURN_180    2750

// Localization
#define MIN_WALL_DISTANCE 8.0
#define ULTRASONIC_MAX_INCHES 157.0

// Grid
#define GRID_ROWS 41
#define GRID_COLS 45

// Headings
#define HEADING_NORTH 0
#define HEADING_EAST  1
#define HEADING_SOUTH 2
#define HEADING_WEST  3

// Rover start
#define START_ROW 31
#define START_COL 22
#define START_HEADING HEADING_NORTH

#endif