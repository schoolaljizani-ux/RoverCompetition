# RoverCompetition

An autonomous mecanum rover that navigates a classroom grid, picks up a cube, and drops it at a target. Built for a robotics course competition. Documented as a dev journal so the messy parts stay visible.

## What it does

- ACEBOTT QD001 rover with mecanum wheels
- 5-DOF robotic arm mounted on top
- ESP32 handles drive and arm
- ESP32 WROVER handles camera and cube detection (teammate's work)
- Laptop runs A* pathfinding in Python with a Pygame visualizer
- Classroom pre-mapped as a 41×45 grid with static obstacles

## Architecture

```
Laptop (Python A*)  ←→  ESP32 (drive + arm)  ←→  ESP32 WROVER (camera)
         Pygame viz          ultrasonic              cube detection
```

Path gets computed on the laptop. Move commands get sent to the rover. Rover executes one cell at a time. Ultrasonic corrects for battery drift as voltage drops.

## Repo structure

- `firmware/` — Arduino sketches for the ESP32 (arm control, movement calibration, integrated)
- `pathfinding/` — Python A* + Pygame visualizer with classroom layout
- `classroom/` — room sketch, measurements, grid math
- `docs/` — dev journal, what broke and how I fixed it
- `tests/` — calibration data

## Hardware

- ACEBOTT QD001 (ESP32 Dev Module, mecanum wheels, ultrasonic)
- 5-DOF servo arm: Base 25, Shoulder 26, Elbow 27, Wrist 33, Gripper 4
- ESP32 WROVER for camera
- Arm neutral positions: Base 128, Shoulder 138, Elbow 180, Wrist 88, Gripper 44

## Status

- [x] A* pathfinding in Python with Pygame visualizer
- [x] Classroom measured and mapped to a grid
- [x] Arm neutral positions calibrated
- [x] Forward movement calibrated (100ms per inch at speed 150)
- [ ] Strafe and turn calibrated
- [ ] Ultrasonic-based position correction
- [ ] Laptop ↔ rover communication
- [ ] Full integration

## Dev journal

Start with [`docs/00-intro.md`](docs/00-intro.md). Journal is chronological. If you want to see specific debugging pain:

- [`docs/03-bluetooth-hell.md`](docs/03-bluetooth-hell.md) — why Bluetooth Classic on macOS Sequoia is cursed
- [`docs/04-voltage-drift.md`](docs/04-voltage-drift.md) — when timing-based movement falls apart
- [`docs/05-classroom-mapping.md`](docs/05-classroom-mapping.md) — turning a messy room into a clean grid

---

**Author:** Abdullah Aljizani
**Course:** La Roche University — Robotics
**Teammate:** Working on cube detection and ML model training
