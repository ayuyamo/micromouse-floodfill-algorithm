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
        if (action == TURNBACK)
            curr_direction = EAST;
        break;
    case NORTH:
        if (action == LEFT)
            curr_direction = WEST;
        if (action == RIGHT)
            curr_direction = EAST;
        if (action == TURNBACK)
            curr_direction = SOUTH;
        break;
    case EAST:
        if (action == LEFT)
            curr_direction = NORTH;
        if (action == RIGHT)
            curr_direction = SOUTH;
        if (action == TURNBACK)
            curr_direction = WEST;
        break;
    case SOUTH:
        if (action == LEFT)
            curr_direction = EAST;
        if (action == RIGHT)
            curr_direction = WEST;
        if (action == TURNBACK)
            curr_direction = NORTH;
        break;
    }
    return curr_direction;
}
Position update_current_state(Position position)
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

Coordinates get_next_location(Coordinates curr_position, Heading curr_direction)
{
    // update coordinates
    switch (curr_direction)
    {
    case WEST:
        --curr_position.x;
        break;
    case NORTH:
        ++curr_position.y;
        break;
    case EAST:
        ++curr_position.x;
        break;
    case SOUTH:
        --curr_position.y;
    }

    return curr_position;
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
        "LEFT", "FORWARD", "RIGHT", "TURNBACK", "IDLE"};

    return actions[action];
}

Action map_coordinates_to_action(Coordinates coord, Heading curr_direction)
{
    Heading cardinal_dir_of_next_pos;
    if (coord.x == 0 && coord.y == 1)
        cardinal_dir_of_next_pos = NORTH;
    else if (coord.x == 0 && coord.y == -1)
        cardinal_dir_of_next_pos = SOUTH;
    else if (coord.x == 1 && coord.y == 0)
        cardinal_dir_of_next_pos = EAST;
    else if (coord.x == -1 && coord.y == 0)
        cardinal_dir_of_next_pos = WEST;

    if (cardinal_dir_of_next_pos == curr_direction)
        return FORWARD;
    else
    {
        switch (curr_direction)
        {
        case NORTH:
            if (cardinal_dir_of_next_pos == EAST)
                return RIGHT;
            else if (cardinal_dir_of_next_pos == WEST)
                return LEFT;
            else if (cardinal_dir_of_next_pos == SOUTH)
                return TURNBACK;
            break;
        case SOUTH:
            if (cardinal_dir_of_next_pos == EAST)
                return LEFT;
            else if (cardinal_dir_of_next_pos == WEST)
                return RIGHT;
            else if (cardinal_dir_of_next_pos == NORTH)
                return TURNBACK;
            break;
        case WEST:
            if (cardinal_dir_of_next_pos == NORTH)
                return RIGHT;
            else if (cardinal_dir_of_next_pos == SOUTH)
                return LEFT;
            else if (cardinal_dir_of_next_pos == EAST)
                return TURNBACK;
            break;
        case EAST:
            if (cardinal_dir_of_next_pos == NORTH)
                return LEFT;
            else if (cardinal_dir_of_next_pos == SOUTH)
                return RIGHT;
            else if (cardinal_dir_of_next_pos == WEST)
                return TURNBACK;
            break;
        }
    }
    return IDLE; // Invalid coordinate
}

Heading get_opposite_direction(Heading curr_direction)
{
    switch (curr_direction)
    {
    case NORTH:
        return SOUTH;
    case SOUTH:
        return NORTH;
    case EAST:
        return WEST;
    case WEST:
        return EAST;
    }
}