#include "navigation.h"
Heading update_direction(Heading curr_direction, Action action)
{
    // update direction
    switch (curr_direction)
    {
    case WEST:
        if (action == LEFT)
            curr_direction = SOUTH;
        if (action == RIGHT)
            curr_direction = NORTH;
        break;
    case NORTH:
        if (action == LEFT)
            curr_direction = WEST;
        if (action == RIGHT)
            curr_direction = EAST;
        break;
    case EAST:
        if (action == LEFT)
            curr_direction = NORTH;
        if (action == RIGHT)
            curr_direction = SOUTH;
        break;
    case SOUTH:
        if (action == LEFT)
            curr_direction = EAST;
        if (action == RIGHT)
            curr_direction = WEST;
        break;
    }
    return curr_direction;
}
Position update_position(Position position)
{
    // update coordinates
    switch (position.direction)
    {
    case WEST:
        --position.coordinates.x;
        break;
    case NORTH:
        ++position.coordinates.y;
        break;
    case EAST:
        ++position.coordinates.x;
        break;
    case SOUTH:
        --position.coordinates.y;
    }

    return position;
}

const char *direction_to_string(Heading dir)
{
    static const char *direction_names[] = {
        "NORTH", "EAST", "SOUTH", "WEST"};

    return direction_names[dir];
}
const char *action_to_string(Action action)
{
    static const char *actions[] = {
        "LEFT", "FORWARD", "RIGHT", "IDLE"};

    return actions[action];
}

Action map_coordinates_to_action(Coordinates coord)
{
    if (coord.x == 0 && coord.y == 1)
        return FORWARD;
    // if (coord.x == 0 && coord.y == -1) return DOWN;
    if (coord.x == 1 && coord.y == 0)
        return RIGHT;
    if (coord.x == -1 && coord.y == 0)
        return LEFT;
    return IDLE; // Invalid coordinate
}