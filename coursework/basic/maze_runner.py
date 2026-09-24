import argparse
import csv
from typing import Tuple, Optional
from maze import Maze


def maze_reader(maze_file: str):
    """
    Read a maze from a file and make a Maze object

    Parameter:
        maze_file: Path to maze file

    Returns:
        A Maze object constructed from the file contents.

    Raises:
        IOError: If file cannot be read.
        ValueError: If the content doesn't form a correct maze.
    """
    # Try to read the file
    try:
        with open(maze_file, 'r') as f:
            lines = f.readlines()
    except FileNotFoundError:
        raise IOError(f"Cannot find file: {maze_file}")
    except PermissionError:
        raise IOError(f"Permission denied reading file: {maze_file}")
    except Exception as e:
        raise IOError(f"Error reading file {maze_file}: {str(e)}")

    # Stripping trailing newlines
    # Help: https://www.w3schools.com/python/ref_string_rstrip.asp
    lines = [line.rstrip('\n') for line in lines]

    if not lines:
        raise ValueError("Empty maze file!")

    # All lines must have the same length
    line_length = len(lines[0])
    for i, line in enumerate(lines):
        if len(line) != line_length:
            raise ValueError(f"Line {i} has inconsistent length")

    # Must have odd number of lines
    # # format: start, walls(even), end -> sum is odd

    if len(lines) % 2 != 1:
        raise ValueError("Invalid maze format: number of lines must be odd")

    width = (line_length - 1) // 2
    height = (len(lines) - 1) // 2
    if width < 1 or height < 1:
        raise ValueError("Maze dimensions must be at least 1x1")

    maze = Maze(width, height)

    # Validating external walls
    # all():
    # Help: https://www.w3schools.com/python/ref_func_all.asp
    if not all(c == '#' for c in lines[0]):
        raise ValueError("Top external wall is incomplete")

    if not all(c == '#' for c in lines[-1]):
        raise ValueError("Bottom external wall is incomplete")

    for line in lines:
        if line[0] != '#':
            raise ValueError("Left external wall is incomplete")
        if line[-1] != '#':
            raise ValueError("Right external wall is incomplete")

    # Parsing the maze
    for line_idx, line in enumerate(lines):
        # Skipping outer borders
        if (line_idx == 0) or (line_idx == len(lines) - 1):
            continue

        # Even lines: Contain horizontal walls and intersections
        if line_idx % 2 == 0:
            # Horizontal wall line
            h_line = height - (line_idx // 2)

            # Horizontal walls
            for col_idx in range(1, line_length - 1, 2):
                x = (col_idx - 1) // 2
                if line[col_idx] == '#':
                    maze.add_horizontal_wall(x, h_line)
                elif line[col_idx] != '.':
                    raise ValueError(
                        f"Invalid character at line {line_idx}, "
                        f"col {col_idx}: expected '#' or '.'"
                    )

            # Intersections
            for col_idx in range(0, line_length, 2):
                if line[col_idx] != '#':
                    raise ValueError(
                        f"Intersection at line {line_idx}, "
                        f"col {col_idx} must be '#'"
                    )

        # Odd lines: Contain cells and vertical walls
        else:
            # Cell row
            y = height - ((line_idx + 1) // 2)

            # Vertical walls
            for col_idx in range(2, line_length - 1, 2):
                v_line = col_idx // 2
                if line[col_idx] == '#':
                    maze.add_vertical_wall(y, v_line)
                elif line[col_idx] != '.':
                    raise ValueError(
                        f"Invalid character at line {line_idx}, "
                        f"col {col_idx}: expected '#' or '.'"
                    )

            # Validating cells
            for col_idx in range(1, line_length - 1, 2):
                if line[col_idx] != '.':
                    raise ValueError(
                        f"Cell at line {line_idx}, "
                        f"col {col_idx} must be '.'"
                    )

    return maze


def parse_position(position_str: str) -> Tuple[int, int]:
    """
    Parsing a pos. string like "2, 1" into coords.

    Parameter
        position_str: A string formatted like "x, y".

    Returns:
        A tuple of (x, y) coords.
    """
    try:
        parts = position_str.split(',')  # Ensures exactly 2 parts (x, y)
        if len(parts) != 2:
            raise ValueError("Position must be in format 'x, y'")

        x = int(parts[0].strip())
        y = int(parts[1].strip())
        return (x, y)

    # ValueError - when int() fails
    # AttributeError - when .split()/.strip() fails
    except (ValueError, AttributeError):
        raise ValueError(f"Invalid position format: {position_str}")


def write_exploration_log(move_history):
    """
    Write exploration log to CSV file (exploration.csv)

    Parameters:
        move_history: List of (x, y, actions) tuples
    """
    try:
        with open('exploration.csv', 'w', newline='') as f:
            writer = csv.writer(f)

            # Write header
            writer.writerow(['Step', 'x-coordinate', 'y-coordinate',
                             'Actions'])

            # Write each step (starting from step 1)
            for step, (x, y, actions) in enumerate(move_history, start=1):
                writer.writerow([step, x, y, actions])

        print(f"Exploration log written to exploration.csv")
    except Exception as e:
        print(f"Warning: Could not write exploration log: {e}")


def write_statistics(maze_file, move_history, path, path_length):
    """
    Writing stats. about maze run into .txt file

    Parameters:
        move_history: No. of exploration steps
        path: List of (x, y) positions in the path
        path_length: Length of path
        filename: Output text filename
    """

    try:
        # Calculate score
        score = move_history / 4 + path_length

        with open('statistics.txt', 'w') as f:
            # Line 1: Name of input file
            f.write(f"{maze_file}\n")

            # Line 2: Score
            f.write(f"{score}\n")

            # Line 3: No. exploration steps
            f.write(f"{move_history}\n")

            # Line 4: Shortest path
            path_str = str(path)
            f.write(f"{path_str}\n")

            # Line 5: Length of shortest path
            f.write(f"{path_length}\n")

        print(f"Statistics written to exploration.txt")

    except Exception as e:
        print(f"Oh dear: Could not write statistics: {e}")


def main():
    """
    Main starting point for running actual maze solver
    """
    # "parser" defines what arguments the program accepts
    # and how to describe them
    parser = argparse.ArgumentParser(description='Welcome to ECS Maze Runner')

    # Positional argument: maze file
    parser.add_argument(
        'maze',  # Argument name
        help='The name of the maze file, e.g., maze1.mz'
    )

    # Optional argument: starting pos.
    parser.add_argument(
        '--starting',
        help='The starting position, e.g., "2, 1"',
        default=None
    )
    # Optional argument: goal pos.
    parser.add_argument(
        '--goal',
        help='The goal position, e.g., "4, 5"',
        default=None
    )

    # Parse command-line arguments provided by the user
    # This automatically handles -h/--help (and invalid arguments)
    args = parser.parse_args()

    try:
        print(f"Reading maze from {args.maze}...")
        # Calling maze reader to parse the file and create Maze object
        maze = maze_reader(args.maze)
        print(f"Maze had been loaded: {maze._width}x{maze._height}")

        # Processing starting pos. (if inputted)
        starting = None
        if args.starting:
            starting = parse_position(args.starting)
            # Checking starting pos. is inside maze boundaries
            if (starting[0] < 0 or starting[0] >= maze._width or
                    starting[1] < 0 or starting[1] >= maze._height):
                raise ValueError(
                    f"Starting position {starting} is out of maze bounds "
                    f"(0-{maze._width-1}, 0-{maze._height-1})!"
                )
            print(f"Starting position: {starting}")
        else:  # Default pos.
            starting = (0, 0)
            print("Starting position: (0, 0) [default]")

        # Processing goal pos. (if inputted)
        goal = None
        if args.goal:
            goal = parse_position(args.goal)
            # Checking goal pos. is inside maze boundaries
            if (goal[0] < 0 or goal[0] >= maze.width or
                    goal[1] < 0 or goal[1] >= maze.height):
                raise ValueError(
                    f"Goal position {goal} is out of maze bounds "
                    f"(0-{maze.width-1}, 0-{maze.height-1})!"
                )
            print(f"Goal position: {goal}")
        else:  # Default pos.
            print(
                f"Goal position: ({maze.width-1}, {maze.height-1}) [default]"
            )

        # Pathfinding
        print("\nFinding shortest path using BFS algorithm")
        path = maze.shortest_path(starting, goal)

        # Extract actual path from exploration log
        if path:
            print(f"\nPath found with {len(path)} steps:")
            print(path)

            # Get exploration log
            # Create a runner to explore and get the log
            if starting:
                explore_start = starting
            else:
                explore_start = (0, 0)

            if goal:
                explore_goal = goal
            else:
                explore_goal = (maze.width - 1, maze.height - 1)

            # Creating runner for exploration
            runner = [explore_start[0], explore_start[1], "N"]
            exploration_log = maze.explore(runner, explore_goal)

            # Writing exploration log to CSV
            write_exploration_log(exploration_log)

            # Calculating stats.
            exploration_steps = len(exploration_log)
            path_length = len(exploration_log)

            # Writing stats.
            write_statistics(args.maze, exploration_steps, path,
                           path_length)

            # Displaying stats.
            print(f"\nStatistics:")
            print(f"Exploration steps: {exploration_steps}")
            print(f"Path length: {path_length}")
            print(f"Score: {exploration_steps / 4 + path_length}")

        else:
            print("\nNo path found between starting and goal positions!")

    except IOError as e:
        print(f"Error reading file: {e}")
    except ValueError as e:
        print(f"Invalid input: {e}")
    except Exception as e:
        print(f"Unexpected error occured: {e}")

    return


if __name__ == "__main__":
    main()
