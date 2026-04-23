# 00 — Intro

This is a competition project for my robotics course. The task: an autonomous rover that navigates a classroom, picks up a cube with a robotic arm, and drops it at a target location.

I'm working with one teammate. They're handling cube detection and training a model to recognize the target. I'm handling pathfinding, movement, and integration.

This journal is chronological. I'm writing it as I go so the debugging pain stays visible. Clean code doesn't teach you anything. The dead ends do.

## Scope

My half of the project:
- A* pathfinding on a grid that represents the classroom
- Translating grid moves into real rover motion
- Battling voltage drift so a 15-minute demo doesn't fall apart
- Communication between laptop and rover
- Arm control for cube pickup and drop

My teammate's half:
- ESP32 WROVER camera setup
- Cube detection via vision
- Model training
- UART communication to send cube info to the main ESP32

## Hardware

- **ACEBOTT QD001** — ESP32-based mecanum rover. Comes with ultrasonic sensor, 4 mecanum wheels, and a shield for easy motor control via a shift register.
- **5-DOF servo arm** — Mounted on top of the rover. Pins: Base 25, Shoulder 26, Elbow 27, Wrist 33, Gripper 4.
- **ESP32 WROVER** — Second microcontroller for the camera. Teammate's work.

## Next

[`01-astar-first.md`](01-astar-first.md) — Starting with pathfinding before any hardware, because I already had a Java A* from a previous class.
