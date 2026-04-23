# 03 — Bluetooth hell on macOS Sequoia

Original plan: laptop sends WASD over WiFi TCP to the rover. Simple socket server on the ESP32, simple socket client in Python.

## Why WiFi didn't work

I needed both the laptop and rover on the same network. Options I had:

1. Create a hotspot on the laptop — macOS Sequoia wouldn't let me enable Internet Sharing from the terminal, and the GUI option didn't appear in System Settings for some reason
2. Use my iPhone hotspot — I don't have one
3. Use existing WiFi — not available in the test environment

Dead end.

Noticed the ESP32 has Bluetooth built in. Pivoted to Bluetooth Classic SPP (Serial Port Profile). On paper, same idea: Python sends bytes over serial, ESP32 reads them and acts. No network needed.

## Why Bluetooth was worse

Uploaded a simple `BluetoothSerial` sketch. Paired my Mac to `TeamA_Rover`. Got the serial port at `/dev/cu.TeamA_Rover`. Python connects without error.

Sent `W\n`. Nothing.

Debug steps:

- Confirmed the ESP32 sketch was running (Serial Monitor showed `Ready`)
- Confirmed Bluetooth paired (System Settings showed connected)
- Confirmed the port existed (`ls /dev/cu.*`)
- Confirmed Python was sending (added `print("Sent: W")`)

But `lsof | grep TeamA_Rover` came back empty. The Python script wasn't actually holding the port open even though `pyserial` reported a successful connection.

## The macOS Sequoia quirk

Sequoia handles Bluetooth Classic SPP in a flaky way. The port appears in `/dev/cu.*` immediately after pairing, but the SPP channel doesn't actually open until some kind of handshake — and on Sequoia, that handshake silently fails in many cases. The port is a dead endpoint.

Tried:

- Unpairing and re-pairing multiple times
- `screen /dev/cu.TeamA_Rover 115200` to force the port open
- Switching from `keyboard` library to `pynput` to rule out input issues
- Removing the `\n` terminator in case the ESP32 `readStringUntil('\n')` was the blocker
- Using a callback instead of polling in the Python script

None of it worked. Data never reached the ESP32.

## Decision

Gave up on wireless for calibration. Went to USB + hardcoded move sequences. Upload a sketch that runs a predetermined movement pattern on boot, unplug, put on the ground, press reset, measure with a ruler.

Loses the "control the rover live" part, but unblocks the actual goal: measuring how movement timing maps to distance. Wireless control becomes a problem for later when I have better network options.

## Lessons

- Every wireless protocol has a hidden dependency on the OS. macOS Sequoia is hostile to ESP32 Bluetooth Classic.
- Don't keep pushing on a broken path when a working path exists. I spent two hours on Bluetooth when hardcoded sequences got me the data I needed in ten minutes.
- Document the failures. Next time someone asks "why not Bluetooth?" I have a straight answer.

## Next

[`04-voltage-drift.md`](04-voltage-drift.md) — calibration works, but battery drain breaks everything.
