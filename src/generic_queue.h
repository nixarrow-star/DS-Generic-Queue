#ifndef GENERIC_QUEUE_H
#define GENERIC_QUEUE_H
#include <stddef.h>
#include <stdlib.h>

struct queue_node
{
    void *data;
    void (*destroy_data)(void *);
    struct queue_node *next;
};

struct queue
{
    size_t size;
    struct queue_node *head;
    struct queue_node *tail;
};

struct queue *queue_init();
struct queue *queue_push(struct queue *queue, void *data, void (*destroy_data)(void *));
void *queue_peek(struct queue *queue);
void *queue_pop(struct queue *queue);
void *queue_destroy(struct queue *queue);

#endif /* GENERIC_QUEUE_H */