#include <stdio.h>
#include "API.h"
#include "navigation.h"
#include <stdbool.h>
#include "queue.h"
#include "floodfill.h"
#include "dimensions.h"

// You do not need to edit this file.
// This program just runs your solver and passes the choices
// to the simulator.

bool goal_reached(Coordinates curr_pos, Coordinates *goal, int num_goals)
{
    for (int i = 0; i < num_goals; i++)
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

    int goal_size = sizeof(goal) / sizeof(goal[0]);

    bool ***walls = initialize_walls_arr();
    int maze[MAZE_ROWS][MAZE_COLS] = {0};
    bool reached_goal = false;
    int num_of_turnbacks = 0;
    reset_maze(maze, walls, goal, goal_size);
    while (!reached_goal)
    {
        Action next_move = floodFill(goal, goal_size, curr_pos, maze, walls);
        char action_buffer[50];
        sprintf(action_buffer, "next action: %s\n", action_to_string(next_move));
        if (strcmp(action_to_string(next_move), "TURNBACK") == 0)
        {
            ++num_of_turnbacks;
        }
        debug_log(action_buffer);
        curr_pos.direction = update_direction(curr_pos.direction, next_move);
        switch (next_move)
        {
        case FORWARD:
            API_moveForward();
            curr_pos = update_current_state(curr_pos);
            break;
        case LEFT:
            API_turnLeft();
            break;
        case RIGHT:
            API_turnRight();
            break;
        case TURNBACK:
            API_turnLeft();
            API_turnLeft();
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
        // API_setColor(curr_pos.coordinates.x, curr_pos.coordinates.y, 'r');
        reached_goal = goal_reached(curr_pos.coordinates, goal, goal_size);
    }

    char turnback_buffer[50]; // Ensure the turnback_buffer is large enough

    // Format the string
    sprintf(turnback_buffer, "number of times mouse turn in opposite direction: %d\n", num_of_turnbacks);
    debug_log(turnback_buffer);

    deallocate_walls_arr(walls);

    return 0;
}