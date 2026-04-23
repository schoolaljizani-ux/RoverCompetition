# Classroom measurements

All measurements taken with a tape measure. Used to build the 41x45 grid in `pathfinding/astar.py`.

## Room

| Dimension | Value |
|-----------|-------|
| Width | 31'8" (380") |
| Length | 29'1" (349") |

## Grid

| | Value |
|-|-|
| Cell size | 8.5" x 8.5" |
| Columns | 45 |
| Rows | 41 |

Cell size = rover body length. Strafes "short" into cells by ~1.5" (body width is 7"), but using a square cell keeps A* math clean.

## Rover

| | Value |
|-|-|
| Length (body) | 8.5" |
| Width (outside edge of wheels) | 7" |
| Wheelbase (front to back wheel center) | 5.5" |
| Wheel radius | 1.5" |
| Wheel circumference | 9.42" |

## Fixed obstacles

### Side counters
- Depth: 27.5" (3 cells)
- Left: cols 0-2
- Right: cols 42-44

### Back counter
- Depth: 29" (3 cells)
- Rows 36-38

### Teacher's desk
- Dimensions: 11'6" x 29.5" (138" x 29.5") = 16 x 3 cells
- 3' from front wall
- Centered horizontally

### Tables (passable)
- Count: 6 (3 rows x 2 columns)
- Dimensions: 131" x 23.5" (15 x 3 cells)
- Flush against side counters
- 3'8" between rows (5 cells)
- 28" from teacher's desk to first table row
- 4' from last table row to back counter
- Middle aisle: 3'10" (5-6 cells)

## Rover start

| | Value |
|-|-|
| Distance from back wall | 6'7" (79") |
| Horizontal position | Center |
| Grid position | (31, 22) |

## Movement calibration

At speed 150:

| Move | Time per inch | Time per cell |
|------|---------------|---------------|
| Forward | 100 ms | 850 ms |
| Backward | 100 ms | 850 ms |
| Strafe left | TBD | TBD |
| Strafe right | TBD | TBD |

Strafe and turn timings still need to be measured.
