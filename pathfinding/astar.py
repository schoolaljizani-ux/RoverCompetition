import heapq
import pygame
import sys

# Grid dimensions based on 31'8" x 29'1" classroom with 8.5" cells
ROWS = 41
COLS = 45
CELL_SIZE = 22

# Colors
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
GREEN = (0, 255, 0)
RED = (255, 0, 0)
BLUE = (0, 0, 255)
LIGHT_GRAY = (200, 200, 200)
GRAY = (150, 150, 150)
DARK_GRAY = (100, 100, 100)
ORANGE = (255, 165, 0)
PURPLE = (128, 0, 128)


class Node:
    def __init__(self, x, y):
        self.x = x
        self.y = y
        self.g = float('inf')
        self.h = 0
        self.f = float('inf')
        self.parent = None
        self.is_obstacle = False
        self.is_table = False
        self.is_explored = False
        self.is_path = False
        self.is_start = False
        self.is_goal = False

    def set_heuristic(self, goal):
        self.h = abs(self.x - goal.x) + abs(self.y - goal.y)

    def calculate_f(self):
        self.f = self.g + self.h

    def __lt__(self, other):
        return self.f < other.f


class AStarVisualizer:
    def __init__(self):
        pygame.init()
        self.screen = pygame.display.set_mode((COLS * CELL_SIZE, ROWS * CELL_SIZE))
        pygame.display.set_caption("A* Pathfinding - Classroom")
        self.grid = [[Node(r, c) for c in range(COLS)] for r in range(ROWS)]

        # Fixed positions
        self.start_pos   = (31, 22)   # 6'7" from back wall, center
        self.pickup_pos  = (15, 8)    # placeholder
        self.dropoff_pos = (15, 36)   # placeholder

        self.path = []
        self.running = True

        self.setup_grid()

    def setup_grid(self):
        # Side counters (27.5" deep = 3 cells)
        for r in range(ROWS):
            for c in range(3):
                self.grid[r][c].is_obstacle = True
            for c in range(42, 45):
                self.grid[r][c].is_obstacle = True

        # Back counter
        for r in range(36, 39):
            for c in range(COLS):
                self.grid[r][c].is_obstacle = True

        # Front wall
        for c in range(COLS):
            self.grid[0][c].is_obstacle = True

        # Teacher's desk (centered, 138" wide = 16 cells, 29.5" tall = 3 cells)
        desk_start = (COLS - 16) // 2
        for r in range(5, 8):
            for c in range(desk_start, desk_start + 16):
                self.grid[r][c].is_obstacle = True

        # Tables - passable (rover drives underneath), but drawn for reference
        table_row_starts = [11, 19, 27]
        for tr_start in table_row_starts:
            for r in range(tr_start, tr_start + 3):
                for c in range(3, 19):
                    self.grid[r][c].is_table = True
                for c in range(26, 42):
                    self.grid[r][c].is_table = True

        # Start and goals
        self.grid[self.start_pos[0]][self.start_pos[1]].is_start = True
        self.grid[self.pickup_pos[0]][self.pickup_pos[1]].is_goal = True
        self.grid[self.dropoff_pos[0]][self.dropoff_pos[1]].is_goal = True

    def reset_search(self):
        for row in self.grid:
            for node in row:
                node.g = float('inf')
                node.f = float('inf')
                node.h = 0
                node.parent = None
                node.is_explored = False
                node.is_path = False

    def astar(self, start_pos, goal_pos):
        self.reset_search()
        open_list = []
        closed_set = set()

        start = self.grid[start_pos[0]][start_pos[1]]
        goal = self.grid[goal_pos[0]][goal_pos[1]]

        start.g = 0
        start.set_heuristic(goal)
        start.calculate_f()
        heapq.heappush(open_list, start)

        while open_list:
            current = heapq.heappop(open_list)
            current.is_explored = True
            closed_set.add((current.x, current.y))
            self.draw()
            pygame.time.delay(10)

            if current.x == goal.x and current.y == goal.y:
                self.reconstruct_path(current)
                return True

            for neighbor in self.get_neighbors(current):
                if (neighbor.x, neighbor.y) in closed_set or neighbor.is_obstacle:
                    continue
                tentative_g = current.g + 1
                if tentative_g < neighbor.g:
                    neighbor.parent = current
                    neighbor.g = tentative_g
                    neighbor.set_heuristic(goal)
                    neighbor.calculate_f()
                    heapq.heappush(open_list, neighbor)

        return False

    def reconstruct_path(self, node):
        self.path = []
        while node is not None:
            self.path.append((node.x, node.y))
            if not node.is_start and not node.is_goal:
                node.is_path = True
            node = node.parent
            self.draw()
            pygame.time.delay(10)
        self.path.reverse()

    def get_neighbors(self, node):
        neighbors = []
        for dx, dy in [(-1, 0), (1, 0), (0, -1), (0, 1)]:
            nx, ny = node.x + dx, node.y + dy
            if 0 <= nx < ROWS and 0 <= ny < COLS:
                neighbors.append(self.grid[nx][ny])
        return neighbors

    def draw(self):
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                sys.exit()

        self.screen.fill(WHITE)
        for row in self.grid:
            for node in row:
                x, y = node.y * CELL_SIZE, node.x * CELL_SIZE
                r, c = node.x, node.y

                if (r, c) == self.start_pos:
                    color = GREEN
                elif (r, c) == self.pickup_pos:
                    color = ORANGE
                elif (r, c) == self.dropoff_pos:
                    color = PURPLE
                elif node.is_path:
                    color = BLUE
                elif node.is_obstacle:
                    color = BLACK
                elif node.is_table:
                    color = DARK_GRAY
                elif node.is_explored:
                    color = LIGHT_GRAY
                else:
                    color = WHITE

                pygame.draw.rect(self.screen, color, (x, y, CELL_SIZE, CELL_SIZE))
                pygame.draw.rect(self.screen, GRAY, (x, y, CELL_SIZE, CELL_SIZE), 1)

        pygame.display.flip()

    def run(self):
        print("Phase 1: Navigating to pickup...")
        found = self.astar(self.start_pos, self.pickup_pos)
        if found:
            print(f"Pickup path found. Steps: {len(self.path) - 1}")
            for step in self.path:
                print(step)
        else:
            print("No path to pickup.")
            return

        print("\nPhase 2: Navigating to dropoff...")
        found = self.astar(self.pickup_pos, self.dropoff_pos)
        if found:
            print(f"Dropoff path found. Steps: {len(self.path) - 1}")
            for step in self.path:
                print(step)
        else:
            print("No path to dropoff.")

        while self.running:
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    self.running = False
            self.draw()

        pygame.quit()


if __name__ == "__main__":
    viz = AStarVisualizer()
    viz.run()
