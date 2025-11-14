#include "generic_queue.h"

//Init the queue
struct queue *queue_init()
{
    struct queue *queue = calloc(1, sizeof(struct queue));
    return queue;
}

//Push the data to the front
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
    node->prev = NULL;
    
    //Link to prev
    if(node->next != NULL)
    {
        node->next->prev = node;
    }

    //Queue update
    queue->head = node;

    if(queue->size == 0)
    {
        queue->tail = node;
    }

    queue->size++;
    return queue;
}

//Show the data on the back
void *queue_peek(struct queue *queue)
{
    if(!queue || queue->size == 0)
    {
        return NULL;
    }

    return queue->tail->data;
}

//Get the data on the back and pop it
void *queue_pop(struct queue *queue)
{
    if(!queue || queue->size == 0)
    {
        return NULL;
    }

    //Get the data
    struct queue_node *node_to_ret = queue->tail;
    void *data = node_to_ret->data;

    //If only one element
    if(queue->size == 1)
    {
        queue->head = NULL;
        queue->tail = NULL;
    }
    else
    {
        queue->tail = queue->tail->prev;
    }

    //Queue update
    queue->size--;
    free(node_to_ret);
    return data;
}

//Destroy all the node
static void queue_node_destroy(struct queue_node *node)
{
    if(!node)
    {
        queue_node_destroy(node->next);
        node->destroy_data(node->data);
        free(node);
    }
}

//Destroy the queue
void queue_destroy(struct queue *queue)
{
    if(!queue)
    {
        queue_node_destroy(queue->head);
        free(queue);
    }
}