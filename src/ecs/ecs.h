#pragma once

#include <stddef.h>
#include <stdint.h>

#include "containers.h"
#include "entity_id.h"
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

/// initialises the ecs using with the component order given.
/// the last va_arg must be a 0, otherwise function will not work correctly
__attribute__((sentinel)) EcsState ecs_init(size_t init_cap, ...);
#define SHORT_ECS_INIT(init_cap, ...) ecs_init(init_cap, __VA_ARGS__, NULL)

/// creates an entity with components provided.
/// returns the EntityId to the newly-created entity.
/// SAFETY: the value before sentinel must be -1. sentinel will not be used, but is included as a reminder to use -1
__attribute__((sentinel)) EntityId init_entity(EcsState* const state, ...);
#define SHORT_INIT_ENTITY(state, ...) init_entity(state, __VA_ARGS__, -1, NULL)

void kill_entity(EcsState *const state, EntityId entity);

/// SAFETY: the value before sentinel must be -1. sentinel will not be used, but is included as a reminder to use -1
__attribute__((sentinel)) QueryResult get_all_components(EcsState* const state, ...);
#define ECS_GET_ALL_COMPONENTS(state, ...) get_all_components(state, __VA_ARGS__, -1, NULL)

// TODO: think about whether indexing should be done via mask or va args
//EntityQueryResult get_entity_components(EcsState *const state, uint64_t mask);

/// SAFETY: the value before sentinel must be -1. sentinel will not be used, but is included as a reminder to use -1
__attribute__((sentinel)) EntityQueryResult get_entity_components(EcsState *const state, EntityId entity, ...);
#define ECS_GET_ENTITY_COMPONENTS(state, entity, ...) get_entity_components(state, entity, __VA_ARGS__, -1, NULL)

