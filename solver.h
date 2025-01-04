#ifndef SOLVER_H
#define SOLVER_H

#include "navigation.h"
#include "dimensions.h"
#include <stdbool.h>

Action solver(Coordinates *goal, int goal_size, Position curr_position, int maze[MAZE_ROWS][MAZE_COLS], bool ***walls);
Action leftWallFollower();
Action floodFill(Coordinates *goal, int goal_size, Position curr_pos, int maze[MAZE_ROWS][MAZE_COLS], bool ***walls);

#endif