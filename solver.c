#include "solver.h"
#include "API.h"
#include "queue.h"
#include "floodfill.h"

Action solver(Coordinates *goal, int goal_size, Position curr_position, int maze[MAZE_ROWS][MAZE_COLS], bool ***walls)
{
    // return leftWallFollower();
    return floodFill(goal, goal_size, curr_position, maze, walls);
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
Action floodFill(Coordinates *goal, int goal_size, Position curr_pos, int maze[MAZE_ROWS][MAZE_COLS], bool ***walls)
{
    //  if wall front --> save curr coords into not use list --> reset whole maze again
    if (API_wallFront())
    {
        update_walls_info(curr_pos.coordinates, curr_pos.direction, walls);
        reset_maze(maze, walls, goal, goal_size);
        if (API_wallLeft())
        {
            Heading cardinal_directions_to_wall_left = update_direction(curr_pos.direction, LEFT);
            update_walls_info(curr_pos.coordinates, cardinal_directions_to_wall_left, walls);
            reset_maze(maze, walls, goal, goal_size);
            return RIGHT;
        }
    }
    if (API_wallLeft())
    {
        Heading cardinal_directions_to_wall_left = update_direction(curr_pos.direction, LEFT);
        update_walls_info(curr_pos.coordinates, cardinal_directions_to_wall_left, walls);
    }
    if (API_wallRight())
    {
        Heading cardinal_directions_to_wall_right = update_direction(curr_pos.direction, RIGHT);
        update_walls_info(curr_pos.coordinates, cardinal_directions_to_wall_right, walls);
    }
    reset_maze(maze, walls, goal, goal_size);
    // mouse picks cells with smaller manhattan distance
    return get_next_move(maze, curr_pos, walls);
}