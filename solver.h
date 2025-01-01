#ifndef SOLVER_H
#define SOLVER_H

#include "navigation.h"
#include <stdbool.h>

Action solver(Coordinates *goal, Position curr_position, int maze[16][16], bool ***walls);
Action leftWallFollower();
Action floodFill(Coordinates *goal, Position curr_pos, int maze[16][16], bool ***walls);

#endif