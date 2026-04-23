# 01 — A* first, hardware later

I had an A* implementation in Java from a previous class. Grid-based, Manhattan heuristic, works fine for 4-direction movement. The plan was to port it to Python so I could build a live visualizer with Pygame.

## Why Python

The rover will run a laptop alongside it. The laptop handles pathfinding, the rover just executes moves. Python made sense because:

- Pygame for real-time grid visualization
- Easier to serialize moves over WiFi/Bluetooth later
- The A* itself is lightweight, no need for C++ performance

## Port

Dropped the Java into Python. Straightforward:

- `Node` class with `g`, `h`, `f`, parent pointer, obstacle flag
- Priority queue via `heapq`
- Manhattan heuristic since moves are 4-directional
- Reconstruct path by walking parent pointers backward

## Visualizer

Pygame draws each cell as a square. Colors:
- Green = start
- Orange = pickup
- Purple = dropoff
- Black = obstacle
- Dark gray = tables (passable, rover clears underneath)
- Light gray = explored
- Blue = final path
- White = unexplored

Added a small `pygame.time.delay(10)` in the main A* loop so I can watch the search expand in real time. Makes debugging 10x easier when something goes wrong.

## What I got wrong early

First run, the grid was too small (37×39) because I guessed at room dimensions instead of measuring. Wasted half an hour.

Second run, I had the start position colliding with a table placement because I didn't think about coordinate order (row, col) vs (x, y). Rover "spawned" inside a wall. Fixed by standardizing on `(row, col)` everywhere.

## Next

[`02-arm-calibration.md`](02-arm-calibration.md) — moving to the hardware side, starting with the arm because it's the simpler system.
