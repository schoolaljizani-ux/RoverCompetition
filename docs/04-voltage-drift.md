# 04 — Voltage drift

With hardcoded sequences, calibration was fast.

## The measurement

Uploaded a sketch that moved forward at speed 150 for exactly 1000ms. Put the rover on the ground, fresh battery, pressed reset, marked where it started and where it stopped.

**Result: 10 inches in 1000ms.**

So: 100ms per inch.

One body length is 8.5 inches (rover chassis edge to edge). Round trip: 850ms per cell forward at speed 150.

## The problem

I did this calibration with a full battery. Then I asked myself: what happens at 50% charge? At 20%?

Motors on a lower voltage spin slower. Same 850ms command, shorter distance. After 10 minutes of demo time, the rover thinks it's at cell (20, 15) but is physically at (18, 15). A* has no idea.

Our demo is 10-15 minutes long. Pure timing-based movement will drift badly over that window.

## Options I considered

**Wheel encoders** — measure actual rotations, ignore time entirely. Accurate regardless of voltage. But the QD001's motors don't have encoders. Retrofitting them means replacing the motors, which means replacing most of the drivetrain.

**IMU-based dead reckoning** — MPU6050 accelerometer + gyro. Good for heading correction during rotations. Bad for forward distance because accelerometer double-integration accumulates massive error.

**Camera-based odometry** — visual tracking of floor features or ceiling markers via the WROVER. Accurate but heavy on compute and takes a lot of setup. Not realistic for our timeline.

**Ultrasonic reference correction** — I already have a forward-facing ultrasonic on the rover. Use it.

## The plan

The classroom is pre-mapped. That means every fixed obstacle (walls, counters, teacher's desk, table legs) is at a known grid position.

Periodically, the rover pings the ultrasonic. It knows what distance the sensor *should* read based on its believed grid position. If the actual reading is off, the rover is drifting.

Correction formula:

```
expected_distance = expected_cells_to_wall * 8.5
drift_ratio = expected_distance / actual_ultrasonic_reading
new_time_per_cell = old_time_per_cell * drift_ratio
```

Self-correcting. Works regardless of battery state. Doesn't need new hardware.

## Where this breaks

Ultrasonic only faces forward. Won't help with strafe drift directly. Will have to either:

- Rotate the rover to face a reference surface before correcting
- Add more ultrasonic sensors on other sides (later upgrade)
- Accept that strafe will be less accurate than forward/back

For now I'll live with the single sensor and see how bad the strafe drift actually is. If it's under a half-cell over 10 minutes, it's fine.

## Next

[`05-classroom-mapping.md`](05-classroom-mapping.md) — turning the room into a grid.
