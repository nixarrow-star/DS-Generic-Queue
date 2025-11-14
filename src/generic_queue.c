#include "generic_queue.h"

struct queue *queue_init()
{
    struct queue *queue = calloc(1, sizeof(struct queue));
    return queue;
}

struct queue *queue_push(struct queue *queue, void *data, void (*destroy_data)(void *))
{
    if(queue == NULL || data == NULL || destroy_data == NULL)
    {
        return NULL;
    }

    //node creation
    struct queue_node *node = calloc(1, sizeof(struct queue_node));
    node->data = data;
    node->destroy_data = destroy_data;
    node->next = queue->head;

    //Queue update
    queue->head = node;

    if(queue->size == 0)
    {
        queue->tail = node;
    }

    queue->size++;
    return queue;
}