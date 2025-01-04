#ifndef FLOODFILL_H
#define FLOODFILL_H

#include "navigation.h"
#include "dimensions.h"
#include <stdbool.h>

#define MAX_NEIGHBOR_WALLS 4

void reset_maze(int maze[MAZE_ROWS][MAZE_COLS], bool ***walls, Coordinates *goals, int goal_size);
Coordinates *get_neighbors(Coordinates coordinates, bool ***walls, int *num_neighbors);
Action get_next_move(int maze[MAZE_ROWS][MAZE_COLS], Position curr_pos, bool ***walls);
bool ***initialize_walls_arr();
void deallocate_walls_arr(bool ***walls);
void update_walls_info(Coordinates curr_location, Heading direction, bool ***walls);
#endif