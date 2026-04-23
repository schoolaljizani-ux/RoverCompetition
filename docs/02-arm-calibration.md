# 02 — Arm calibration

5-DOF arm, 5 servos. Pins locked in:

- Base: 25
- Shoulder: 26
- Elbow: 27
- Wrist: 33
- Gripper: 4

## The rule I learned the hard way

When you call `servo.attach(pin)` on an ESP32, the servo immediately snaps to whatever position it was last written to — which is often a garbage value from boot, or an angle the servo hit in a previous run. That means attaching all 5 servos at once can cause the arm to violently slam into something before you've had a chance to tell it where to go.

I damaged one elbow servo early on by doing exactly this. The arm flung itself around on boot. Had to replace it with an MG90S.

## The fix

Attach one servo at a time. Immediately write the neutral angle. Add a small delay. Then move to the next.

```cpp
gripper.attach(4);   gripper.write(44);   delay(500);
wrist.attach(33);    wrist.write(88);     delay(500);
elbow.attach(27);    elbow.write(180);    delay(500);
shoulder.attach(26); shoulder.write(138); delay(500);
base.attach(25);     base.write(128);     delay(500);
```

Order matters too. Start with the lightest-load joints first (gripper, wrist), then work down to the load-bearing base. That way the arm doesn't try to swing a full extension before it knows where it's supposed to be.

## Finding neutral

To find neutral for each joint, I wrote a little jog utility — attach one servo at a time, use `W` to increase angle and `S` to decrease angle, hit `N` to confirm and move to the next joint. The jog version is commented out at the top of `firmware/arm_neutral/arm_neutral.ino` for reference.

Final neutral positions:

| Joint | Angle |
|-------|-------|
| Base | 128 |
| Shoulder | 138 |
| Elbow | 180 |
| Wrist | 88 |
| Gripper | 44 |

These are the positions where the arm is folded compactly on top of the rover, nothing sticking out that could get caught.

## Critical rule going forward

Every single sketch I write for the rover starts with `setupArm()` that puts the arm in neutral before doing anything else. The arm is now the first thing that initializes on boot, before WiFi, Bluetooth, ultrasonic, anything. That way if anything crashes later, the arm is at least in a safe position.

## Next

[`03-bluetooth-hell.md`](03-bluetooth-hell.md) — trying to control the rover from my laptop.
