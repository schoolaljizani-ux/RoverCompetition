# 05 — Classroom mapping

To use ultrasonic correction, the rover needs to know where static obstacles are. That means pre-mapping the classroom as a grid.

## Room measurements

- Room: 31'8" × 29'1" (380" × 349")
- Cell size: 8.5" × 8.5" (based on rover body length)
- Grid: 41 rows × 45 columns

Why 8.5 × 8.5 and not asymmetric 8.5 × 7? Asymmetric cells complicate A* math. Using a square cell means the rover "strafes short" (7" into an 8.5" cell), leaving a small gap, which is fine for navigation accuracy.

## Obstacles

**Side counters** (27.5" deep):
- Left: cols 0-2
- Right: cols 42-44

**Back counter** (29" deep, rows 36-38)

**Front wall** (row 0)

**Teacher's desk** (11'6" × 29.5" = 138" × 29.5"):
- Rows 5-7 (3 cells tall)
- Centered horizontally at cols 14-29 (16 cells wide)

**Tables** — 6 tables, 3 rows × 2 columns, each 131" × 23.5":
- Passable by the rover (it clears underneath)
- But table legs matter for ultrasonic reference
- Table rows at approximately rows 11-13, 19-21, 27-29
- Left column tables: cols 3-18
- Right column tables: cols 26-41
- Middle aisle: cols 19-25

**Rover start position:** (31, 22) — 6'7" from back wall, horizontally centered.

## Why tables are marked "passable but visible"

Drew them in dark gray on the Pygame visualizer so I can see where they are, but A* treats them as open cells. The rover drives under them. Tables are low enough that the chassis clears the underside without hitting anything.

This only works because chairs will be removed from the classroom during the demo. With chairs present, the space under the tables becomes obstacle-heavy. Without them, it's a straight shot.

## Ultrasonic reference points

Now that the map exists, every static obstacle becomes a reference:

- Front wall: rover can ping forward from anywhere in the room, expect a specific distance
- Teacher's desk: big target, great forward reference
- Back counter: same but from the rear (if we add a rear ultrasonic)
- Table legs: closer-range references when navigating between tables

The rover's believed position maps to an expected ultrasonic reading. Drift shows up as a difference. Simple and reliable.

## Next

Integration. WiFi/Bluetooth problem still needs solving, but at least the pathfinding logic is solid.
