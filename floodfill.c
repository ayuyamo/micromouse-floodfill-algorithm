#include "floodfill.h"
#include "queue.h"
#include <limits.h>
#include <string.h>
#include <stdio.h>

bool valid_position(int x, int y)
{
    if (0 <= x && x < MAZE_ROWS && 0 <= y && y < MAZE_COLS)
    {
        return true;
    }
    return false;
}
void reset_maze(int maze[MAZE_ROWS][MAZE_COLS], bool walls[MAZE_ROWS][MAZE_COLS][MAX_NEIGHBOR_WALLS], Coordinates *goals, int goal_size)
{
    // Create a boolean 2D array to mark locations that are goals
    bool is_goal[MAZE_ROWS][MAZE_COLS] = {false};

    // Reset all the maze tiles to 0
    for (int i = 0; i < MAZE_ROWS; i++)
    {
        memset(maze[i], 0, MAZE_COLS * sizeof(int));
    }

    // Mark the goal coordinates in the lookup table
    for (int k = 0; k < goal_size; k++)
    {
        is_goal[goals[k].x][goals[k].y] = true;
    }

    // Iterate through the 16x16 grid
    for (int i = 0; i < MAZE_ROWS; i++)
    {
        for (int j = 0; j < MAZE_COLS; j++)
        {
            // If the coordinate is not a goal, clear the text
            if (!is_goal[i][j])
            {
                API_clearText(i, j);
            }
        }
    }
    // Initialize a boolean array to track which maze tiles have had their Manhattan distance calculated and displayed in the simulator
    bool text_set[MAZE_ROWS][MAZE_COLS] = {false};

    for (int k = 0; k < goal_size; k++)
    {
        text_set[goals[k].x][goals[k].y] = true;
    }

    // Queue implemented for floodfill
    Queue *queue = initialize_queue();

    // Set all text of goals in maze to 0 and add each goal into the queue
    for (int i = 0; i < goal_size; i++)
    {
        API_setText(goals[i].x, goals[i].y, "0");
        Node *new_node = initialize_node(goals[i].x, goals[i].y, 0);
        enqueue(queue, new_node);
    }
    while (!is_empty(queue))
    {
        // Dequeue the next node to process
        Node *curr_node = dequeue(queue);
        // Get all valid neighbors of the current node
        int num_neighbors;
        Coordinates *neighbors = get_neighbors(curr_node->coordinates, walls, &num_neighbors);
        // Iterate through each neighbor
        for (int i = 0; i < num_neighbors; i++)
        {
            // Check if the neighbor's Manhattan distance has not been set and is a valid tile
            if ((!(text_set[neighbors[i].x][neighbors[i].y])) && (neighbors[i].x != -1) && (neighbors[i].y != -1))
            {
                // Calculate the Manhattan distance for the neighbor and convert it to a string
                char manhattan_distance_str[20];
                sprintf(manhattan_distance_str, "%d", curr_node->manhattan_distance + 1);

                // Update the simulator display with the calculated Manhattan distance
                API_setText(neighbors[i].x, neighbors[i].y, manhattan_distance_str);

                // Set the calculated Manhattan distance in the maze representation
                maze[neighbors[i].x][neighbors[i].y] = curr_node->manhattan_distance + 1;

                // Initialize a new node for this neighbor with the updated distance
                Node *new_node = initialize_node(neighbors[i].x, neighbors[i].y, curr_node->manhattan_distance + 1);

                // Mark this tile as having its Manhattan distance set
                text_set[neighbors[i].x][neighbors[i].y] = true;

                // Enqueue the new node for further processing
                enqueue(queue, new_node);
            }
        }
        free(curr_node);
    }
    free(queue);
}

Coordinates *get_neighbors(Coordinates coordinates, bool walls[MAZE_ROWS][MAZE_COLS][MAX_NEIGHBOR_WALLS], int *num_neighbors)
{
    // Define the movement directions in terms of coordinate changes
    Coordinates map[] = {
        {0, 1},   // UP = NORTH
        {1, 0},   // RIGHT = EAST
        {0, -1},  // DOWN = SOUTH
        {-1, 0}}; // LEFT = WEST

    // Calculate the size of the 'map' array to determine the number of possible directionss
    int map_size = sizeof(map) / sizeof(map[0]);
    // Set the number of neighbors based on the size of the map array
    (*num_neighbors) = map_size;
    Coordinates *neighbors = malloc(map_size * sizeof(Coordinates));

    int coord_x;
    int coord_y;
    // Iterate over each direction in the map to calculate potential neighbor coordinates
    for (int i = 0; i < map_size; i++)
    {
        // Calculate the new coordinates based on the current position and direction
        coord_x = coordinates.x + map[i].x;
        coord_y = coordinates.y + map[i].y;

        // Check if the neighbor is within maze bounds and not blocked by a wall
        if ((!walls[coordinates.x][coordinates.y][i]) && valid_position(coord_x, coord_y))
        {
            neighbors[i].x = coord_x;
            neighbors[i].y = coord_y;
        }
        else
        {
            neighbors[i].x = -1; // NULL
            neighbors[i].y = -1; // NULL
        }
    }
    return neighbors;
}

Action get_next_move(int maze[MAZE_ROWS][MAZE_COLS], Position curr_pos, bool walls[MAZE_ROWS][MAZE_COLS][MAX_NEIGHBOR_WALLS])
{
    // Get the neighboring coordinates of the current position, along with the number of valid neighbors
    int num_neighbors;
    Coordinates *neighbors = get_neighbors(curr_pos.coordinates, walls, &num_neighbors);
    Coordinates next_pos;
    int min_dist = INT_MAX;

    // Iterate through each neighbor to determine the one with the smallest Manhattan distance
    for (int i = 0; i < num_neighbors; i++)
    {
        // Ensure the neighbor is valid (i.e., not marked as (-1, -1), which indicates an invalid neighbor)
        if ((neighbors[i].x != -1) && (neighbors[i].y != -1))
        {
            // Log the current neighbor's position and its Manhattan distance for debugging purposes
            char neighbor_buffer[50];
            sprintf(neighbor_buffer, "neighbor: (%d, %d) -- manhattan distance: %d\n", neighbors[i].x, neighbors[i].y, maze[neighbors[i].x][neighbors[i].y]);
            debug_log(neighbor_buffer);

            // If this neighbor has a smaller Manhattan distance, update the next position
            if (min_dist > maze[neighbors[i].x][neighbors[i].y])
            {
                min_dist = maze[neighbors[i].x][neighbors[i].y];
                next_pos.x = neighbors[i].x;
                next_pos.y = neighbors[i].y;
            }
        }
    }
    // Compare the next position with the current position and log the difference in coordinates
    char diff_buffer[50];
    sprintf(diff_buffer, "next pos: (%d, %d)\n", next_pos.x - curr_pos.coordinates.x, next_pos.y - curr_pos.coordinates.y);
    debug_log(diff_buffer);

    // Calculate the difference in coordinates (direction of movement) and return the corresponding action
    Coordinates diff = {next_pos.x - curr_pos.coordinates.x, next_pos.y - curr_pos.coordinates.y};
    return map_coordinates_to_action(diff, curr_pos.direction);
}

void update_walls_info(Coordinates curr_location, Heading direction, bool walls[MAZE_ROWS][MAZE_COLS][MAX_NEIGHBOR_WALLS])
{
    Position pos_separated_by_wall;
    pos_separated_by_wall.coordinates = get_next_location(curr_location, direction);
    pos_separated_by_wall.direction = get_opposite_direction(direction);

    // Mark the current location and direction as blocked by a wall
    walls[curr_location.x][curr_location.y][direction] = true;

    // Ensure the new position (after the move) is within valid bounds of the maze (0 to 15 for both x and y coordinates)
    if (valid_position(pos_separated_by_wall.coordinates.x, pos_separated_by_wall.coordinates.y))
    {
        // Mark the wall at the new position and its direction (opposite of the current direction)
        walls[pos_separated_by_wall.coordinates.x][pos_separated_by_wall.coordinates.y][pos_separated_by_wall.direction] = true;
    }
}

// Put your implementation of floodfill here!
Action floodFill(Coordinates *goal, int goal_size, Position curr_pos, int maze[MAZE_ROWS][MAZE_COLS], bool walls[MAZE_ROWS][MAZE_COLS][MAX_NEIGHBOR_WALLS])
{
    // Every time a wall is detected, update locations where wall is found and reset the maze
    //  Case wall in front & enter corner
    if (API_wallFront())
    {
        update_walls_info(curr_pos.coordinates, curr_pos.direction, walls);
        reset_maze(maze, walls, goal, goal_size);
        if (API_wallLeft())
        {
            Heading cardinal_directions_to_wall_left = update_direction(curr_pos.direction, LEFT);
            update_walls_info(curr_pos.coordinates, cardinal_directions_to_wall_left, walls);
            reset_maze(maze, walls, goal, goal_size);
            return RIGHT; // helps the mouse turn around if it reaches a deadend
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

    // Return the next move based on the smallest Manhattan distance from the current position
    return get_next_move(maze, curr_pos, walls);
}