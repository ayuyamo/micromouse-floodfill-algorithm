#ifndef NAVIGATION_H
#define NAVIGATION_H

typedef enum Heading
{
    NORTH,
    EAST,
    SOUTH,
    WEST
} Heading;
typedef enum Action
{
    LEFT,
    FORWARD,
    RIGHT,
    IDLE
} Action;

typedef struct
{
    int x;
    int y;
} Coordinates;

typedef struct
{
    Coordinates coordinates;
    Heading direction;
} Position;

Heading update_direction(Heading curr_direction, Action action);
Position update_position(Position position);
const char *direction_to_string(Heading dir);
const char *action_to_string(Action action);
Action map_coordinates_to_action(Coordinates coord);

#endif