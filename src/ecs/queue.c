#include <stdio.h>
#include <stdlib.h>

#include "entity_id.h"
#include "queue.h"

void
push(EntityQueue* const queue, EntityId id)
{
    Node* new = malloc(sizeof(typeof(*new)));
    new->value = id;
    new->next = NULL;

    queue->last->next = new;
}

EntityId
pop(EntityQueue* const queue)
{
    if (is_empty(queue)) {
        printf("cannot pop a value from an empty queue\n");
        exit(1);
    }

    EntityId id = queue->first->value;

    Node* old = queue->first;
    queue->first = queue->first->next;
    free(old);

    return id;
}

inline bool
is_empty(const EntityQueue* const queue)
{
    return queue->first == NULL;
}
