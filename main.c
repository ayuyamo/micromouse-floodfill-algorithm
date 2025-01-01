#include <stdio.h>
#include "solver.h"
#include "API.h"
#include "navigation.h"
#include <stdbool.h>
#include "queue.h"
#include "floodfill.h"

// You do not need to edit this file.
// This program just runs your solver and passes the choices
// to the simulator.

bool goal_reached(Coordinates curr_pos, Coordinates *goal)
{
    int goal_size = sizeof(goal) / sizeof(goal[0]);
    for (int i = 0; i < goal_size; i++)
    {
        if (curr_pos.x == goal[i].x && curr_pos.y == goal[i].y)
        {
            return true;
        }
    }
    return false;
}
int main(int argc, char *argv[])
{
    debug_log("Running...");
    Position curr_pos = {0, 0, NORTH}; // starting position
    Coordinates goal[] = {
        {7, 7},
        {7, 8},
        {8, 7},
        {8, 8}};

    bool ***walls = initialize_walls_arr();
    int maze[16][16] = {0};
    bool reached_goal = false;
    while (!reached_goal)
    {
        Action nextMove = solver(goal, curr_pos.coordinates, maze, walls);
        curr_pos.direction = update_direction(curr_pos.direction, nextMove);
        switch (nextMove)
        {
        case FORWARD:
            API_moveForward();
            curr_pos = update_position(curr_pos);
            break;
        case LEFT:
            API_turnLeft();
            break;
        case RIGHT:
            API_turnRight();
            break;
        case IDLE:
            break;
        }
        // print coordinates after each action
        // Buffer to hold the resulting string
        char buffer[50]; // Ensure the buffer is large enough

        // Format the string
        sprintf(buffer, "curr position: (%d, %d)  Direction: %s", curr_pos.coordinates.x, curr_pos.coordinates.y, direction_to_string(curr_pos.direction));
        debug_log(buffer);
        API_setColor(curr_pos.coordinates.x, curr_pos.coordinates.y, 'r');
        reached_goal = goal_reached(curr_pos.coordinates, goal);
    }

    deallocate_walls_arr(walls);
}