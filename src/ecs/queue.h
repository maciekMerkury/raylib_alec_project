#pragma once

#include <stdbool.h>

#include "entity_id.h"

// FIXME: This is kinda ugly and inconsisten, find a better way of doing that
typedef struct Node Node;

struct Node {
    EntityId value;
    Node* next;
};

typedef struct {
    Node* first;
    Node* last;
} FIFOQueue;

/// pushes the id to the end of the queue
void push(FIFOQueue* const queue, EntityId id);

/// pops an id from the top of the queue.
/// will panic if the queue is empty
EntityId pop(FIFOQueue* const queue);

/// returns true if the queue is empty
bool is_empty(const FIFOQueue* const queue);
