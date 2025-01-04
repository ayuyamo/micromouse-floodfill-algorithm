#include "floodfill.h"
#include "queue.h"
#include <limits.h>
#include <string.h>
#include <stdio.h>

// TODO: reset maze properly
void reset_maze(int maze[MAZE_ROWS][MAZE_COLS], bool ***walls, Coordinates *goals, int goal_size)
{
    // create a queue
    // clear all text
    // set the cells at the goal to 0
    // Create a 16x16 lookup table initialized to false
    bool is_goal[MAZE_ROWS][MAZE_COLS] = {false};
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
    bool text_set[MAZE_ROWS][MAZE_COLS] = {false};

    for (int k = 0; k < goal_size; k++)
    {
        text_set[goals[k].x][goals[k].y] = true;
    }
    Queue *queue = initialize_queue();
    for (int i = 0; i < goal_size; i++)
    {
        API_setText(goals[i].x, goals[i].y, "0");
        Node *new_node = initialize_node(goals[i].x, goals[i].y, 0);
        enqueue(queue, new_node);
    }
    while (!is_empty(queue))
    {
        Node *curr_node = dequeue(queue);
        int num_neighbors;
        Coordinates *neighbors = get_neighbors(curr_node->coordinates, walls, &num_neighbors);
        for (int i = 0; i < num_neighbors; i++)
        {
            // char curr_coords[50];
            // sprintf(curr_coords, "Currently at coords: (%d, %d)", neighbors[i].x, neighbors[i].y);
            // debug_log(curr_coords);
            if ((!(text_set[neighbors[i].x][neighbors[i].y])) && (neighbors[i].x != -1) && (neighbors[i].y != -1))
            {
                char manhattan_distance_str[20];
                sprintf(manhattan_distance_str, "%d", curr_node->manhattan_distance + 1);
                API_setText(neighbors[i].x, neighbors[i].y, manhattan_distance_str);
                maze[neighbors[i].x][neighbors[i].y] = curr_node->manhattan_distance + 1;

                Node *new_node = initialize_node(neighbors[i].x, neighbors[i].y, curr_node->manhattan_distance + 1);
                text_set[neighbors[i].x][neighbors[i].y] = true;

                // char node_info[50];
                // sprintf(node_info, "New node added: (%d, %d, %d) ", new_node->coordinates.x, new_node->coordinates.y, new_node->manhattan_distance);
                // debug_log(node_info);
                enqueue(queue, new_node);
            }
        }
        free(curr_node);
    }
    free(queue);
}

Coordinates *get_neighbors(Coordinates coordinates, bool ***walls, int *num_neighbors)
{
    Coordinates map[] = {
        {0, 1},   // UP = NORTH
        {1, 0},   // RIGHT = EAST
        {0, -1},  // DOWN = SOUTH
        {-1, 0}}; // LEFT = WEST

    int map_size = sizeof(map) / sizeof(map[0]);
    (*num_neighbors) = map_size;
    Coordinates *neighbors = malloc(map_size * sizeof(Coordinates));

    int coord_x;
    int coord_y;
    for (int i = 0; i < map_size; i++)
    {
        coord_x = coordinates.x + map[i].x;
        coord_y = coordinates.y + map[i].y;
        if ((!walls[coordinates.x][coordinates.y][i]) && (0 <= coord_x && coord_x < MAZE_COLS) && (0 <= coord_y && coord_y < MAZE_ROWS))
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

Action get_next_move(int maze[MAZE_ROWS][MAZE_COLS], Position curr_pos, bool ***walls)
{
    int num_neighbors;
    Coordinates *neighbors = get_neighbors(curr_pos.coordinates, walls, &num_neighbors);
    Coordinates next_pos;
    int min_dist = INT_MAX;
    for (int i = 0; i < num_neighbors; i++)
    {
        if ((neighbors[i].x != -1) && (neighbors[i].y != -1))
        {
            char neighbor_buffer[50];
            sprintf(neighbor_buffer, "neighbor: (%d, %d) -- manhattan distance: %d\n", neighbors[i].x, neighbors[i].y, maze[neighbors[i].x][neighbors[i].y]);
            debug_log(neighbor_buffer);
            if (min_dist > maze[neighbors[i].x][neighbors[i].y])
            {
                min_dist = maze[neighbors[i].x][neighbors[i].y];
                next_pos.x = neighbors[i].x;
                next_pos.y = neighbors[i].y;
            }
        }
    }
    // compare to current pos --> return action
    char diff_buffer[50];
    sprintf(diff_buffer, "next pos: (%d, %d)\n", next_pos.x - curr_pos.coordinates.x, next_pos.y - curr_pos.coordinates.y);
    debug_log(diff_buffer);
    Coordinates diff = {next_pos.x - curr_pos.coordinates.x, next_pos.y - curr_pos.coordinates.y};
    return map_coordinates_to_action(diff, curr_pos.direction);
}

bool ***initialize_walls_arr()
{
    // allocate space for each row of double pointers (x)
    bool ***walls = (bool ***)malloc(MAZE_ROWS * sizeof(bool **));

    for (int i = 0; i < MAZE_ROWS; i++)
    { // allocate space for each entry (column) in each row (containing single pointer)
        walls[i] = (bool **)malloc(MAZE_COLS * sizeof(bool *));
        for (int j = 0; j < MAZE_COLS; j++)
        { // allocate space for each entry in an array stored in each column
            walls[i][j] = (bool *)malloc(MAX_NEIGHBOR_WALLS * sizeof(bool));

            for (int k = 0; k < MAX_NEIGHBOR_WALLS; k++)
            { // initialize each boolean entry inside an array within each entry inside outer 2d array to false
                walls[i][j][k] = false;
            }
        }
    }
    return walls;
}

void deallocate_walls_arr(bool ***walls)
{
    // freeing dynamically allocated array for storing info about walls
    for (int i = 0; i < MAZE_COLS; i++)
    {
        for (int j = 0; j < MAZE_ROWS; j++)
        {
            free(walls[i][j]);
        }
        free(walls[i]);
    }
    free(walls);
}

void update_walls_info(Coordinates curr_location, Heading direction, bool ***walls)
{
    Position pos_separated_by_wall;
    pos_separated_by_wall.coordinates = get_next_location(curr_location, direction);
    pos_separated_by_wall.direction = get_opposite_direction(direction);
    walls[curr_location.x][curr_location.y][direction] = true;
    if (0 <= pos_separated_by_wall.coordinates.x && pos_separated_by_wall.coordinates.x < 16 && 0 <= pos_separated_by_wall.coordinates.y && pos_separated_by_wall.coordinates.y < 16)
    {
        walls[pos_separated_by_wall.coordinates.x][pos_separated_by_wall.coordinates.y][pos_separated_by_wall.direction] = true;
    }
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