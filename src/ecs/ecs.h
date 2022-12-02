#pragma once

#include <stddef.h>

#include "entity_id.h"
#include "containers.h"
#include "queue.h"

// uint_64 is used for flags in query, which limits the number of component types
#define MAXIMUM_COMPONENT_COUNT 64

typedef struct {
    CompactContainer components[MAXIMUM_COMPONENT_COUNT];
    size_t component_type_count;

    size_t entity_count;
    FIFOQueue empty_entity_queue;
} EcsState;

/// initialises the ecs using with the component order given.
/// the last va_arg must be a 0, otherwise function will not work correctly

__attribute__ ((sentinel)) EcsState ecs_init(size_t init_cap, ...);
