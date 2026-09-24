DFS Maze Solver Implementation
ALGORITHM: DEPTH-FIRST SEARCH (DFS)

OVERVIEW:
This implementation uses recursive Depth-First Search to solve any maze, including non-regular mazes with disconnected walls. Unlike the left-hug algorithm from Part 3, DFS guarantees a solution if a path exists!!!

ALGORITHM DESIGN 
DFS explores as deep as possible along each branch before backtracking. In a way you could say that it mimics human maze exploration: follow a path until a dead end, then backtrack to the last junction and try another path.

KEY COMPONENTS
1. Visited matrix to prevent infinite loops
2. Recursive function for exploration
3. Backtracking when paths fail
4. Base case when goal is reached

MAIN STEPS:

1. Set default positions:

	Start: (0, 0) if not provided

	Goal: (width-1, height-1) if not provided

2. Create visited matrix:

	2D boolean array (height × width)

	All cells initially False (unvisited)

	Prevents revisiting cells

3. Define recursive helper (dfs_helper):
	Base Case:

	If current position equals goal: return current path

	Recursive Case:

		Mark current cell as visited

		Get wall information (north, east, south, west)

		Try each direction in order: N → E → S → W

			If no wall AND cell not visited:

			Recursively call dfs_helper with new position

			Add new position to path

			If recursion returns a path: return it

			If all directions fail: return None (backtrack)

4. Start recursion from starting position

5. Return path if found, else empty list


PSEUDOCODE
if goal is None: goal = (width-1, height-1)

visited = 2D array[height][width] = False

function dfs_helper(x, y, current_path):
    if (x, y) == goal:
        return current_path
    
    visited[y][x] = True
    
    directions = [
        (not north_wall, x, y+1),   # North
        (not east_wall, x+1, y),    # East
        (not south_wall, x, y-1),   # South
        (not west_wall, x-1, y)     # West
    ]
    
    for can_move, next_x, next_y in directions:
        if can_move and not visited[next_y][next_x]:
            result = dfs_helper(next_x, next_y, 
                               current_path + [(next_x, next_y)])
            if result is not None:
                return result
    
    return None  # Backtrack

return dfs_helper(start_x, start_y, [start]) or []



SOURCES USED TO HELP LEARN DFS:
https://www.geeksforgeeks.org/dsa/depth-first-search-or-dfs-for-a-graph/
https://en.wikipedia.org/wiki/Depth-first_search
https://www.datacamp.com/tutorial/depth-first-search-in-python?dc_referrer=https%3A%2F%2Fwww.google.com%2F
