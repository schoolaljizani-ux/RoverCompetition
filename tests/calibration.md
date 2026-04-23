# Calibration data

Raw measurements from the physical rover. Used to calculate move timings.

## Test setup

- Battery: full charge
- Surface: vinyl tile (classroom floor)
- Speed parameter: 150
- Rover: ACEBOTT QD001 with 5-DOF arm mounted on top

## Forward movement

| Time (ms) | Distance (in) | ms per inch |
|-----------|---------------|-------------|
| 1000 | 10.0 | 100 |

Result: **100 ms per inch at speed 150**

For one cell forward (8.5"): **850 ms**

## Strafe / turn

Pending. Will run the calibration sketch with `Move_Left`, `Move_Right`, `Contrarotate`, `Clockwise` and measure each.

## Voltage notes

These numbers are valid at full battery. Movement slows as battery drains. Plan: ultrasonic-based correction during runtime to scale move times up as voltage drops. See `docs/04-voltage-drift.md`.
