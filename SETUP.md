# Setup

## Pathfinding (laptop)

```
pip install pygame
python pathfinding/astar.py
```

Pygame window opens, A* runs from start to pickup, then pickup to dropoff. Path prints to console.

## Firmware (rover)

Arduino IDE with the ESP32 board package installed. Board: **ESP32 Dev Module**.

Required libraries:
- `ESP32Servo`
- `acebott` (vehicle library, comes with the QD001 docs)

To upload:
1. Open the `.ino` file from `firmware/`
2. Select board: ESP32 Dev Module
3. Select port: `/dev/cu.usbserial-110` (Mac) or equivalent
4. Hit upload

## Sketches

- `firmware/arm_neutral/` — initializes the arm to neutral and stops. Run first to confirm the arm is wired correctly.
- `firmware/movement_calibration/` — runs a single forward move on boot. Used to measure ms per inch.

## Common gotchas

**Port busy on upload.** Close Serial Monitor. Run `lsof | grep cu.usbserial` to find what's holding it.

**Arm slams violently on boot.** A servo got `attach()`-ed before being told its target angle. Always `attach()` then immediately `write()` the neutral angle, one joint at a time with a delay between.

**Compile error: `'class vehicle' has no member named 'moveForward'`.** The library's API is `myCar.Move(direction, speed)` with constants like `Forward`, `Backward`, `Move_Left`, `Move_Right`, `Contrarotate`, `Clockwise`, `Stop`. See the source at `~/Documents/Arduino/libraries/acebott/src/vehicle.h`.
