#include <stdio.h>
#include "solver.h"
#include "API.h"
#include "navigation.h"
#include <stdbool.h>
#include "queue.h"

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
    Position curr_pos = {0, 0, NORTH};
    Coordinates goal[] = {
        {7, 7},
        {7, 8},
        {8, 7},
        {8, 8}};
    // // Create a 16x16 lookup table initialized to false
    // bool is_goal[16][16] = {false};

    // // Mark the goal coordinates in the lookup table
    // int goal_size = sizeof(goal) / sizeof(goal[0]);
    // for (int k = 0; k < goal_size; k++)
    // {
    //     is_goal[goal[k].x][goal[k].y] = true;
    // }

    // // Iterate through the 16x16 grid
    // for (int i = 0; i < 16; i++)
    // {
    //     for (int j = 0; j < 16; j++)
    //     {
    //         // If the coordinate is not a goal, clear the text
    //         if (!is_goal[i][j])
    //         {
    //             API_clearText(i, j);
    //         }
    //     }
    // }
    // bool text_set[16][16] = {false};

    // for (int k = 0; k < goal_size; k++)
    // {
    //     text_set[goal[k].x][goal[k].y] = true;
    // }
    // Queue *queue = initialize_queue();
    // for (int i = 0; i < goal_size; i++)
    // {
    //     API_setText(goal[i].x, goal[i].y, "0");
    //     Node *new_node = initialize_node(goal[i].x, goal[i].y, 0);
    //     enqueue(queue, new_node);
    // }
    // while (!is_empty(queue))
    // {
    //     Node *curr_node = dequeue(queue);
    //     Coordinates neighbors[] = {
    //         {curr_node->coordinates.x, curr_node->coordinates.y + 1}, // UP
    //         {curr_node->coordinates.x, curr_node->coordinates.y - 1}, // DOWN
    //         {curr_node->coordinates.x + 1, curr_node->coordinates.y}, // RIGHT
    //         {curr_node->coordinates.x - 1, curr_node->coordinates.y}, // LEFT
    //     };
    //     int num_neighbors = sizeof(neighbors) / sizeof(neighbors[0]);

    //     for (int i = 0; i < num_neighbors; i++)
    //     {
    //         // char curr_coords[50];
    //         // sprintf(curr_coords, "Currently at coords: (%d, %d)", neighbors[i].x, neighbors[i].y);
    //         // debug_log(curr_coords);

    //         if ((0 <= neighbors[i].x && neighbors[i].x < 16) && (0 <= neighbors[i].y && neighbors[i].y < 16) && (!(text_set[neighbors[i].x][neighbors[i].y])))
    //         {
    //             char manhattan_distance_str[20];
    //             sprintf(manhattan_distance_str, "%d", curr_node->manhattan_distance + 1);
    //             API_setText(neighbors[i].x, neighbors[i].y, manhattan_distance_str);

    //             Node *new_node = initialize_node(neighbors[i].x, neighbors[i].y, curr_node->manhattan_distance + 1);
    //             text_set[neighbors[i].x][neighbors[i].y] = true;

    //             // char node_info[50];
    //             // sprintf(node_info, "New node added: (%d, %d, %d) ", new_node->coordinates.x, new_node->coordinates.y, new_node->manhattan_distance);
    //             // debug_log(node_info);
    //             enqueue(queue, new_node);
    //         }
    //     }
    // }
    // debug_log("All cells filled");
    bool reached_goal = false;
    while (!reached_goal)
    {
        Action nextMove = solver(goal, curr_pos.coordinates);
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
}