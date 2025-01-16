#ifndef FLOODFILL_H
#define FLOODFILL_H

#include "navigation.h"
#include "dimensions.h"
#include <stdbool.h>

bool valid_position(int x, int y);
void reset_maze(int maze[MAZE_ROWS][MAZE_COLS], bool walls[MAZE_ROWS][MAZE_COLS][MAX_NEIGHBOR_WALLS], Coordinates *goals, int goal_size);
Coordinates *get_neighbors(Coordinates coordinates, bool walls[MAZE_ROWS][MAZE_COLS][MAX_NEIGHBOR_WALLS], int *num_neighbors);
Action get_next_move(int maze[MAZE_ROWS][MAZE_COLS], Position curr_pos, bool walls[MAZE_ROWS][MAZE_COLS][MAX_NEIGHBOR_WALLS]);
bool ***initialize_walls_arr();
void deallocate_walls_arr(bool walls[MAZE_ROWS][MAZE_COLS][MAX_NEIGHBOR_WALLS]);
void update_walls_info(Coordinates curr_location, Heading direction, bool walls[MAZE_ROWS][MAZE_COLS][MAX_NEIGHBOR_WALLS]);
#endif