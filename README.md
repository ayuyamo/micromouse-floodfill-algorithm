# Maze Solver Using Flood-Fill Algorithm

This project demonstrates how to use the Flood-Fill Algorithm for solving a maze with a simulated mouse. The simulator provides an API for implementing and testing the algorithm. When transitioning to a physical mouse, API calls can be replaced with hardware-specific functions for reading sensors, such as Infrared (IR) sensors.
Flood-Fill Algorithm Overview

- The Flood-Fill Algorithm is an efficient method for finding the shortest path to a goal in a maze. The algorithm works by assigning a "flood value" to each cell of the maze, which represents the number of steps from that cell to the goal.
- Steps:

  - **Initialization**: Assign each cell a large flood value (e.g., infinity), except for the goal cell(s), which are assigned a value of `0`.
  - **Flooding**: Iteratively update flood values by checking neighboring cells and ensuring each cell has a value one greater than the minimum of its accessible neighbors.
  - **Pathfinding**: The mouse starts from the current cell, moves to the neighboring cell with the smallest flood value, and repeats until the goal is reached.

## Simulator Setup

Implementing the flood-fill algorithm directly onto your physical mouse can be impractical and time-consuming. Testing would require repeatedly uploading code to the mouse and running it through the maze after every small code change—making debugging tedious and inefficient.

Instead, you can use a micromouse simulation, which models the mouse's movement through a virtual maze. This allows you to test and refine your algorithm in a controlled environment, ensuring it works correctly before porting it to the physical hardware.

### Instructions to Set Up the Simulator

- For Windows:
  Follow these [Windows setup instructions](https://docs.google.com/presentation/d/1tr_2cUcouLl3fvlSyOth7XXo3jRbpBw1TfRX8yWRETY/edit?usp=sharing).

- For MacOS / Linux:
  Follow these [MacOS/Linux setup instructions](https://docs.google.com/presentation/d/18rHwcIJNPsIRkun7N9Wq5YYAiFSc-rkyNcAQBOEolg4/edit?usp=share_link).

This implementation uses the `MMS Simulator`. The API details can be found at the [MMS GitHub page](https://github.com/mackorone/mms#mouse-api).

### Key Functions in the Simulator API

- `API_moveForward()`: Moves the mouse forward.
- `API_turnRight()` / `API_turnLeft()`: Rotates the mouse in place. -` API_wallLeft()` / `API_wallRight()` / `API_wallFront()`: Detects whether there is a wall in the respective direction.
- `API_setColor(x, y, color)`: Updates the visual representation of a maze tile in the simulator (useful for debugging).
- `API_setText(x, y, text)`: Updates the text displayed on a specific maze tile in the simulator. This feature is particularly useful for debugging and visualizing the flood-fill algorithm because it provides real-time insights into the flood values calculated for each tile.

## Implementation

### Algorithm Logic in the Simulator

- Flood-Value Assignment: Assign initial flood values for all cells.
- Wall Detection: Use the API_wallFront(), API_wallLeft(), and API_wallRight() functions to detect walls and update flood values accordingly.
- Movement: Use the API_moveForward() function to navigate through the maze.
- Visualization (Optional): Use API_setColor() to visualize the flood values and the mouse's path in the simulator.
