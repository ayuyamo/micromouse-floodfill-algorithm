#ifndef QUEUE_H
#define QUEUE_H
#include <stdbool.h>
#include <stdlib.h>
#include "navigation.h"

typedef struct Node
{
    Coordinates coordinates;
    int manhattan_distance;
    struct Node *next;
} Node;

typedef struct
{
    Node *front;
    Node *rear;
} Queue;

Node *initialize_node(int x, int y, int dist);
Queue *initialize_queue();
void enqueue(Queue *queue, Node *node);
Node *dequeue(Queue *queue);
bool is_empty(Queue *queue);
#endif