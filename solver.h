#ifndef SOLVER_H
#define SOLVER_H

#include "navigation.h"

Action solver(Coordinates *goal, Coordinates curr_position);
Action leftWallFollower();
Action floodFill(Coordinates *goal);

#endif