#include "queue.h"
#include "API.h"
#include <stdio.h>

Node *initialize_node(int x, int y, int dist)
{
    Node *new_node = (Node *)malloc(sizeof(Node));
    Coordinates coords = {x, y};
    new_node->coordinates = coords;
    new_node->manhattan_distance = dist;
    new_node->next = NULL;
    return new_node;
}
Queue *initialize_queue()
{
    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->front = NULL;
    q->rear = NULL;
    return q;
}
void enqueue(Queue *queue, Node *node)
{
    if (is_empty(queue))
    {
        queue->front = node;
        queue->rear = node;
    }
    else
    {
        queue->rear->next = node;
        queue->rear = node;
    }
}
Node *dequeue(Queue *queue)
{
    if (is_empty(queue))
    {
        debug_log("Queue is empty, cannot dequeue.");
        return NULL;
    }
    Node *temp = queue->front;
    queue->front = queue->front->next;
    if (queue->front == NULL)
    {
        queue->rear = NULL;
    }
    return temp;
}
bool is_empty(Queue *queue)
{
    return queue->front == NULL && queue->rear == NULL;
}
