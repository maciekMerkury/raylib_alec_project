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
} EntityQueue;

/// pushes the id to the end of the queue
void push(EntityQueue* const queue, EntityId id);

/// pops an id from the top of the queue.
/// will panic if the queue is empty
EntityId pop(EntityQueue* const queue);

/// returns true if the queue is empty
bool is_empty(const EntityQueue* const queue);
