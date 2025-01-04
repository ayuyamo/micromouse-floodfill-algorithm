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
    // TODO: need to fix how i set walls
    //  if wall front --> save curr coords into not use list --> reset whole maze again
    if (API_wallFront())
    {
        Position front_pos_separated_by_wall = update_position(curr_pos);
        front_pos_separated_by_wall.direction = get_opposite_direction(curr_pos.direction);
        walls[curr_pos.coordinates.x][curr_pos.coordinates.y][curr_pos.direction] = true;
        if (0 <= front_pos_separated_by_wall.coordinates.x && front_pos_separated_by_wall.coordinates.x < 16 && 0 <= front_pos_separated_by_wall.coordinates.y && front_pos_separated_by_wall.coordinates.y < 16)
        {
            walls[front_pos_separated_by_wall.coordinates.x][front_pos_separated_by_wall.coordinates.y][front_pos_separated_by_wall.direction] = true;
        }
        reset_maze(maze, walls, goal, goal_size);
        if (API_wallLeft())
        {
            Position pos_on_left;
            pos_on_left.coordinates = curr_pos.coordinates;
            pos_on_left.direction = update_direction(curr_pos.direction, LEFT);
            pos_on_left = update_position(pos_on_left); // update coordinates
            walls[curr_pos.coordinates.x][curr_pos.coordinates.y][pos_on_left.direction] = true;
            if (0 <= pos_on_left.coordinates.x && pos_on_left.coordinates.x < 16 && 0 <= pos_on_left.coordinates.y && pos_on_left.coordinates.y < 16)
            {
                // Heading direction_with_wall = update_direction(curr_pos.direction, LEFT);
                // walls[curr_pos.coordinates.x][curr_pos.coordinates.y][direction_with_wall] = true;
                pos_on_left.direction = get_opposite_direction(pos_on_left.direction);
                walls[pos_on_left.coordinates.x][pos_on_left.coordinates.y][pos_on_left.direction] = true;
            }
            reset_maze(maze, walls, goal, goal_size);
            return RIGHT;
        }
    }
    // mouse picks cells with smaller manhattan distance
    return get_next_move(maze, curr_pos, walls);
}