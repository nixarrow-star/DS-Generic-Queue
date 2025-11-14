
# 🚚 Generic Queue Library (C)

A lightweight and fully generic **queue implementation** in C.  
It allows you to enqueue, dequeue, and peek at any kind of data safely, using `void*` pointers and user-defined destroy functions.

---

## ✅ Features

- Generic queue supporting any data type  
- Push (enqueue), Pop (dequeue), and Peek operations  
- Automatic memory cleanup with custom destroy functions  
- Doubly-linked list internally for efficient operations  
- Clean and dependency-free

---

## 📦 Data Structures

### `struct queue_node`
Represents a single node of the queue:

```c
struct queue_node
{
    void *data;                       // Pointer to stored data
    void (*destroy_data)(void *);     // Function used to free the data
    struct queue_node *next;          // Pointer to the next node (toward tail)
    struct queue_node *prev;          // Pointer to the previous node (toward head)
};
```

✔ Each node owns its data  
✔ When destroyed, `destroy_data(data)` is automatically called

---

### `struct queue`
Represents the entire queue:

```c
struct queue
{
    size_t size;              // Number of elements in the queue
    struct queue_node *head;  // First element (front)
    struct queue_node *tail;  // Last element (back)
};
```

- `head` is the element to dequeue next  
- `tail` is the newest element added  
- `size` increases on push and decreases on pop

---

## 🔧 API Documentation

### `struct queue *queue_init();`
Initializes an empty queue.

- On success → returns a valid empty queue  
- On allocation failure → returns `NULL`

---

### `struct queue *queue_push(struct queue *queue, void *data, void (*destroy_data)(void *));`
Adds a new element (`data`) at the **back** of the queue.

- `destroy_data` will be used later when the queue is destroyed  
- Does **not** copy the data, only stores the pointer

- On success → returns `queue`  
- On allocation failure → returns `NULL`

---

### `void *queue_peek(struct queue *queue);`
Returns the **front** element of the queue without removing it.

- On success → returns the `void*` data  
- On empty queue → returns `NULL`

---

### `void *queue_pop(struct queue *queue);`
Removes the **front** element of the queue and returns its data pointer.

- The node is freed  
- `destroy_data` is **NOT** called → the caller now owns the data

- On success → returns the data pointer  
- On empty queue → returns `NULL`

---

### `void queue_destroy(struct queue *queue);`
Destroys the entire queue and all its elements.

- Frees every node  
- Calls each stored `destroy_data(data)` before freeing

⚠ **WARNING:**  
> The queue automatically destroys all stored data.  
> Only call this when you no longer need the data.

---

## ✅ Example Usage

```c
void free_int(void *n)
{
    free(n);
}

int main()
{
    struct queue *q = queue_init();
    if (!q) return 1;

    int *x = malloc(sizeof(int));
    *x = 7;

    queue_push(q, x, free_int);

    int *peeked = queue_peek(q);
    printf("Front: %d\n", *peeked);

    int *popped = queue_pop(q);
    printf("Popped: %d\n", *popped);
    free(popped);

    queue_destroy(q);
}
```

---

## ✅ License

Free to use and modify in any project.
