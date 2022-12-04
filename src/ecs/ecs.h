#pragma once

#include <stddef.h>
#include <stdint.h>

#include "entity_id.h"
#include "containers.h"
#include "queue.h"

// uint_64 is used for flags in query, which limits the number of component types
#define MAXIMUM_COMPONENT_COUNT 64

typedef struct {
    CompactContainer components[MAXIMUM_COMPONENT_COUNT];
    int component_type_count;

    size_t entity_count;

    /// The maximum number of elements that can fit in the currently allocated memory
    size_t entity_capacity;

    EntityQueue dead_entity_queue;
} EcsState;

typedef struct {
    const size_t component_type_count;

    /// The indeces corresponding to the component type in EcsState
    const int *const component_indices;
    CompactContainer*const *const components;
} QueryResult;

typedef struct {
    const size_t component_type_count;

    const int *const component_indices;
    GenericComponent *const components;
} EntityQueryResult;


#define todo(thing) static_assert(false, "unfinished: " #thing "\n")
#define SHORT_ECS_INIT(init_cap, ...) ecs_init(init_cap, __VA_ARGS__, NULL)

/// initialises the ecs using with the component order given.
/// the last va_arg must be a 0, otherwise function will not work correctly
__attribute__((sentinel)) EcsState ecs_init(size_t init_cap, ...);

/// creates an entity with components provided.
/// returns the EntityId to the newly-created entity
__attribute__((sentinel)) EntityId init_entity(EcsState* const state, ...);

