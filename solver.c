#include "solver.h"
#include "API.h"
#include "queue.h"
#include "floodfill.h"

Action solver(Coordinates *goal, Position curr_position, int maze[16][16], bool ***walls)
{
    // return leftWallFollower();
    return floodFill(goal, curr_position, maze, walls);
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
Action floodFill(Coordinates *goal, Position curr_pos, int maze[16][16], bool ***walls)
{
    // if wall front --> save curr coords into not use list --> reset whole maze again
    if (API_wallFront())
    {
        walls[curr_pos.coordinates.x][curr_pos.coordinates.y][curr_pos.direction] = true;
    }
    reset_maze(maze, walls, goal);
    // mouse picks cells with smaller manhattan distance
    return get_next_move(maze, curr_pos.coordinates, walls);
}