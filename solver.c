#include "solver.h"
#include "API.h"
#include "queue.h"
#include "floodfill.h"

Action solver(Coordinates *goal, Coordinates curr_position)
{
    // return leftWallFollower();
    return floodFill(goal, curr_position);
}

// This is an example of a simple left wall following algorithm.
Action leftWallFollower()
{
    if (API_wallFront())
    {
        if (API_wallLeft())
        {
            return RIGHT;
        }
        return LEFT;
    }
    return FORWARD;
}

// Put your implementation of floodfill here!
Action floodFill(Coordinates *goal, Coordinates curr_pos)
{
    /*
    TODO: fix the set up of maze below
    */

    int maze[16][16] = {0};
    // reset_maze(maze, walls, goal);
    // return get_next_move(maze, curr_pos, walls);
    // reset maze  with prefilled values
    // mouse picks cells with smaller manhattan distance
    // TODO: if wall front --> save curr coords into not use list --> reset whole maze again
}