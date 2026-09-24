# ECS Maze Runner Coursework
 
## Files
 
### Core Modules
- `runner.py` - Runner representation and movement functions
- `maze.py` - Maze class implementation
- `maze_runner.py` - Maze reader and command-line interface
 
### Additional Files
- `exploration.csv` - Exploration log output
- `statistics.txt` - Maze-solving statistics output
 
## Features
 
### Part 1
- Create and manage runners
- Turn left/right
- Move forward
 
### Part 2
- Create mazes with configurable dimensions
- Add horizontal and vertical walls
- Query wall information
 
### Part 3
- Sense nearby walls
- Safe movement within the maze
- Maze exploration using the left-hug algorithm
 
### Part 4
- Compute a shortest path between two positions
 
### Part 5
- Read maze definitions from `.mz` files
- Command-line support using `argparse`
- Input validation and error handling
 
### Part 6
- Generate exploration logs (`exploration.csv`)
- Generate statistics reports (`statistics.txt`)
 
## Running
 
```bash
python maze_runner.py maze1.mz
