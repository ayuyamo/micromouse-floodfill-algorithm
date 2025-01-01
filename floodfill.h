#ifndef FLOODFILL_H
#define FLOODFILL_H

#include "navigation.h"
#include <stdbool.h>

// void initialize_maze();
void reset_maze(int maze[16][16], bool ***walls, Coordinates *goals);
Coordinates *get_neighbors(Coordinates coordinates, bool ***walls);
Action get_next_move(int maze[16][16], Coordinates curr_pos, bool ***walls);
bool ***initialize_walls_arr();
void deallocate_walls_arr(bool ***walls);
#endif