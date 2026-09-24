from typing import Tuple, List, Optional


class Maze:
    def __init__(self, width: int = 5, height: int = 5):
        """
        Initialise new maze with specified dimensions and outer boundaries

        The maze created has all interior walls open (False) and all outer
        walls closed (True) - like an empty room with walls!

        Parameters:
            width: No. of horizontal cells (default: 5)
            height: No. of vertical cells (default: 5)
        """
        self._width = width
        self._height = height

        # Set up horizontal walls
        # Note: horizontal[y][x] means the wall ABOVE cell (x, y)
        self._horizontal_walls = []
        for h_line in range(height + 1):
            row = []
            for col in range(width):
                if (h_line == 0) or (h_line) == height:
                    row.append(True)  # top/bottom boundaries
                else:
                    row.append(False)
            self._horizontal_walls.append(row)

        # Set up vertical walls.
        # Note: vertical[y][x] means the vertical wall at x = v_line at row y
        self._vertical_walls = []
        for y in range(height):
            row = []
            for v_line in range(width + 1):
                if v_line == 0 or v_line == width:
                    row.append(True)  # left/right boundaries
                else:
                    row.append(False)
            self._vertical_walls.append(row)

    @property
    def width(self) -> int:
        """
        Returns width of maze (no. of horizontal cells)
        """
        return self._width

    @property
    def height(self) -> int:
        """
        Returns height of maze (no. of vertical cells)
        """
        return self._height

    def add_horizontal_wall(self, x_coordinate: int, horizontal_line: int):
        """
        Add horizontal wall that blocks north-south movement

        A horiz. wall at line h blocks movement between:
        - Cell (x, h-1) and cell (x, h) (where h > 0)

        Parameters:
            x_coordinate: The x-coord. for where wall is placed.
            horizontal_line: The horiz. line number (0 to height)
        """
        self._horizontal_walls[horizontal_line][x_coordinate] = True

    def add_vertical_wall(self, y_coordinate: int, vertical_line: int):
        """
        Add horizontal wall that blocks north-south movement

        A vert. wall at line h blocks movement between:
        - Cell (v-1, y) and cell (v, y) (if v > 0)

        Parameters:
            x_coordinate: The x-coord. for where wall is placed.
            vertical_line: The vertical line number (0 to width)
        """
        self._vertical_walls[y_coordinate][vertical_line] = True

    def get_walls(self, x_coordinate: int,
                  y_coordinate: int) -> Tuple[bool, bool, bool, bool]:
        """
        Get wall info. for all 4 sides of a cell

        Parameters:
            x_coordinate: The x-coord. of the cell (0 to width-1)
            y_coordinate: The y-coord. of the cell (0 to height-1)

        Returns:
            Tuple of four booleans (north, east, south, west):
            - north: True if wall exists to the north (y+1 direction)
            - east: True if wall exists to the east (x+1 direction)
            - south: True if wall exists to the south (y-1 direction)
            - west: True if wall exists to the west (x-1 direction)
        """
        north_wall = self._horizontal_walls[y_coordinate + 1][x_coordinate]
        south_wall = self._horizontal_walls[y_coordinate][x_coordinate]
        east_wall = self._vertical_walls[y_coordinate][x_coordinate + 1]
        west_wall = self._vertical_walls[y_coordinate][x_coordinate]

        return (north_wall, east_wall, south_wall, west_wall)

    def sense_walls(self, runner) -> Tuple[bool, bool, bool]:
        """
        Detecting walls based off of the runner's position and orientation

        Parameter:
             runner: [x, y, orientation]

        Returns:
            Tuple of three booleans (left, front, right):
            - left: True if wall exists to the runner's left
            - front: True if wall exists directly in front of runner
            - right: True if wall exists to the runner's right
        """
        x, y, orientation = runner
        north, east, south, west = self.get_walls(x, y)

        if orientation == "N":
            left_wall = west
            front_wall = north
            right_wall = east
        elif orientation == "E":
            left_wall = north
            front_wall = east
            right_wall = south
        elif orientation == "S":
            left_wall = east
            front_wall = south
            right_wall = west
        else:  # orientation == "W"
            left_wall = south
            front_wall = west
            right_wall = north

        return (left_wall, front_wall, right_wall)

    def go_straight(self, runner) -> Tuple[int, int, str]:
        """
        Move the runner forward one cell (depending on orinetation of runner),
        if possible

        Parameter:
            runner: [x, y, orientation]

        Returns:
            Updated runner: [x, y, orientation]

        Raises:
            ValueError: If there is a wall in front of the runner
        """
        _, front, _ = self.sense_walls(runner)

        if front:
            raise ValueError("Cannot move forward - there's a wall in front!")

        x, y, orinetation = runner

        if orinetation == "N":
            y += 1
        elif orinetation == "E":
            x += 1
        elif orinetation == "S":
            y -= 1
        else:  # facing == "W"
            x -= 1

        runner = [x, y, orinetation]
        return runner

    def move(self, runner) -> Tuple:
        """
        Execute one step of left-hug algorithm
        Keep left hand on the wall!

        Priority order:
        1. go left
        2. go straight
        3. go right
        4. go back

        Parameter:
            runner: [x, y, orientation]

        Returns:
            - Tuple: (updated_runner, action_sequence)
            - Action sequence string:
                "LF": Turn left then go forward
                "F": Go forward
                "RF": Turn right then go forward
                "B": Turn back then go forward
        """
        left_wall_exists, front_wall_exists, right_wall_exists = self.sense_walls(runner)
        directions = ["N", "E", "S", "W"]
        orinetation_idx = directions.index(runner[2])

        # 1. Go left
        if not left_wall_exists:
            runner[2] = directions[(orinetation_idx - 1) % 4]
            runner = self.go_straight(runner)
            return (runner, "LF")

        # 2. Go straight
        if not front_wall_exists:
            runner = self.go_straight(runner)
            return (runner, "F")

        # 3. Go right
        if not right_wall_exists:
            runner[2] = directions[(orinetation_idx + 1) % 4]
            runner = self.go_straight(runner)
            return (runner, "RF")

        # 4. Go back
        runner[2] = directions[(orinetation_idx + 2) % 4]
        runner = self.go_straight(runner)
        return (runner, "B")

    def explore(self, runner, goal: Optional[Tuple[
        int, int]] = None) -> List[
            Tuple[int, int, str]]:
        """
        Explore the maze from start to goal using the left-hug algorithm

        Parameters:
            runner: [x, y, orientation]
            goal: Optional (x, y) target pos.

        Returns:
            List of tuples to show the exploration history:
            Each tuple: (x_before, y_before, action_sequence)
            - x_before, y_before: Pos. before taking the action
            - action_sequence: String that describes the move
              ("LF", "F", "RF", "B")
        """

        # If input goal is None
        # -> target pos. is top-right corner of the input maze
        if goal is None:
            goal_x = self._width - 1
            goal_y = self._height - 1
        else:
            goal_x, goal_y = goal

        move_history = []

        while (runner[0] != goal_x) or (runner[1] != goal_y):
            current_x = runner[0]
            current_y = runner[1]
            runner, actions = self.move(runner)
            move_history.append((current_x, current_y, actions))

        return move_history

    def shortest_path(self, starting: Optional[Tuple[int, int]
            ] = None, goal: Optional[
            Tuple[int, int]] = None) -> List[Tuple[int, int]]:
        """
        Finding shortest path from starting pos. to goal pos.

        This func.performs two phases:
        1. Exploration phase: Uses a runner with left-hug to
           discover the maze layout
        2. Pathfinding phase: Uses Breadth-First Search (BFS)
           to find shortest path

        Parameters:
            starting: Optional (x, y) starting pos.
                      Default: (0, 0) .
            goal: Optional (x, y) goal pos.
                  Default: the top-right-hand corner

        Returns:
            List of (x, y) tuples showing shortest path from
            starting to goal, with no repetitions or gaps

        Note:
            Pathfinding algorithm may NOT necessarily be
            the fastest due to nature of left-hug algorithm
        """
        # Set default starting pos. (bottom-left)
        if starting is None:
            start_x, start_y = 0, 0
        else:
            start_x, start_y = starting

        # Set default goal position (top-right)
        if goal is None:
            goal_x = self._width - 1
            goal_y = self._height - 1
        else:
            goal_x, goal_y = goal

        # Step 1: Use runner to explore and gather info.
        # Create runner at starting pos.
        explorer_runner = [start_x, start_y, "N"]

        # Explore to goal to get maze info.
        self.explore(explorer_runner, (goal_x, goal_y))
        # Gather wall info.

        # Step 2: Using BFS to find shortest path
        # Queue stores: (x, y, path_so_far)
        queue = [(start_x, start_y, [(start_x, start_y)])]

        # Track visited positions using 2D list
        visited = []
        for y in range(self._height):
            row = []
            for x in range(self._width):
                row.append(False)
            visited.append(row)

        visited[start_y][start_x] = True

        while queue:
            current_x, current_y, path = queue.pop(0)

            # Check if we've reached the goal
            if current_x == goal_x and current_y == goal_y:
                return path

            # Get walls around current pos.
            north, east, south, west = self.get_walls(current_x, current_y)

            # Try moving in each direction (if no wall blocks it)

            # move_options -> (can_move, dx, dy)
            move_options = [
               (not north, 0, 1),   # North
               (not east, 1, 0),    # East
               (not south, 0, -1),  # South
               (not west, -1, 0)    # West
            ]

            for can_move, dx, dy in move_options:
                if can_move:
                    next_x = current_x + dx
                    next_y = current_y + dy

                    if not visited[next_y][next_x]:
                        visited[next_y][next_x] = True
                        new_path = path + [(next_x, next_y)]
                        queue.append((next_x, next_y, new_path))

        # If no path was found, return empty list
        return []
