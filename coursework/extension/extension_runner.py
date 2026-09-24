# SAME AS runner.py

# 4 given cardinal directions, i.e., "N", "E", "W", "S

def create_runner(x: int = 0, y: int = 0, orientation: str = "N"):
    """
    Create and return a runner represented as
    [x, y, orientation].

    Runner is a 3-element list:
    - Index 0: x-coord.
    - Index 1: y-coord.
    - Index 2: orientation ("N", "E", "S", "W")

    Parameters:
        x: Initial x-coord. (defualt: 0)
        y: Initial y-coord. (defualt: 0)
    """
    return [x, y, orientation]


def get_x(runner):
    """
    Get x coord. of a runner

    Parameters:
        runner: [x, y, orientation]

    Returns:
        int: The x-coord. of the runner
    """
    x = runner[0]
    return x


def get_y(runner):
    """
    Get x coord. of a runner

    Parameters:
        runner: [x, y, orientation]

    Returns:
        int: The y-coord. of the runner
    """
    y = runner[1]
    return y


def get_orientation(runner):
    """
    Get orientation of a runner

    Parameters:
        runner: [x, y, orientation]

    Returns:
        str: orientation ("N", "E", "S", or "W")
    """
    orientation = runner[2]
    return orientation


def turn(runner, direction: str):
    """
    Turn runner left or right.

    Directions rotate clockwise:
        N -> E -> S -> W -> N

    Parameters:
        runner: [x, y, orientation]
        direction: "Left" or "Right"

    Returns:
        list: Updated runner with new orientation
    """
    # Define the four cardinal directions in clockwise order
    compass_directions = ("N", "E", "S", "W")
    current_direction_index = compass_directions.index(runner[2])

    # Turning runner - i used to change direction
    if direction == "Right":
        i = 1
    else:  # Left
        i = -1

    new_direction_index = abs(current_direction_index + i) % 4
    orientation = compass_directions[new_direction_index]

    # Replace old orinetation
    runner.pop()
    runner.append(orientation)

    return runner


def forward(runner):
    """
    Move runner forward one cell based on its orientation

    Parameters:
        runner: [x, y, orientation]

    Returns:
        list: Updated runner with new coordinates
    """
    orientation = runner[2]
    x = runner[0]
    y = runner[1]

    if orientation == "N":
        y += 1
    if orientation == "S":
        y -= 1
    if orientation == "E":
        x += 1
    if orientation == "W":
        x -= 1

    return [x, y, orientation]
