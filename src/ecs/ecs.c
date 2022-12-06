#include <assert.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "containers.h"
#include "ecs.h"
#include "entity_id.h"
#include "queue.h"

#define REALLOC_INCREASE 8

/// set handles to null and free memory
void
reset_components(EcsState* const state, EntityId id)
{
    if (id.id > state->entity_count) {
        printf("trying to access an invalid entity. id = %lu, entity_count = %lu\n", id.id, state->entity_count);
        exit(1);
    }

    for (int i = 0; i < state->component_type_count; ++i) {
        free(state->components[i].data[id.id]);
        state->components[i].data[id.id] = NULL;
    }
}

EcsState
ecs_init(size_t init_cap, ...)
{
    EcsState state = {0};
    state.entity_capacity = init_cap;

    va_list ap;
    va_start(ap, init_cap);

    for (int size = va_arg(ap, size_t); size > -1; size = va_arg(ap, size_t)) {
        void** data = calloc(sizeof(typeof(*data)), init_cap);
        if (!data) {
            printf("[%s; %d]:\tcould not malloc %lu bytes\n", __FILE__, __LINE__, sizeof(void*) * init_cap);
            perror("malloc error: ");
            exit(1);
        }

        state.components[state.component_type_count] = (CompactContainer){.element_size = size, .data = data};

        if (++state.component_type_count >= MAXIMUM_COMPONENT_COUNT) {
            printf("No more than 64 component types are permitted, see ecs.h for more details\n");
            exit(1);
        }
    }
    va_end(ap);

    return state;
}

EntityId
init_entity(EcsState* const state, ...)
{
    EntityId id;

    if (!is_empty(&state->dead_entity_queue)) {
        id = pop(&state->dead_entity_queue);
    } else {
        id = (EntityId){state->entity_count++};

        if (state->entity_count > state->entity_capacity) {
            state->entity_capacity += REALLOC_INCREASE;

            for (int i = 0; i < state->component_type_count; ++i) {
                CompactContainer* cont = &state->components[i];

                cont->data = reallocarray(cont->data, state->entity_capacity, sizeof(typeof(*cont->data)));
                if (!cont->data) {
                    printf("could not resize the component type %i. new size was supposed to be %lu\n", i,
                           state->entity_capacity);
                    perror("malloc error: ");
                    exit(1);
                }
            }
        }
    }

    reset_components(state, id);

    va_list ap;
    va_start(ap, state);

    for (int i = va_arg(ap, size_t); i > -1; i = va_arg(ap, size_t)) {
        if (i >= state->component_type_count) {
            printf("trying to access component out of bounds. i = %i, component_type_count = %i\n", i,
                   state->component_type_count);
            exit(1);
        }

        state->components[i].data[id.id] = calloc(1, state->components[i].element_size);
    }

    va_end(ap);

    return id;
}

void
kill_entity(EcsState* const state, EntityId entity)
{
    if (entity.id >= state->entity_count) {
        printf("trying to kill an entity outside of entity_count. id = %lu, count = %lu", entity.id,
               state->entity_count);
        exit(1);
    }

    reset_components(state, entity);
    push(&state->dead_entity_queue, entity);
}

QueryResult
get_all_components(EcsState* const state, ...)
{

    size_t component_type_count = 0;
    int* component_indices = calloc(state->component_type_count, sizeof(typeof(*component_indices)));
    CompactContainer** components = calloc(state->component_type_count, sizeof(typeof(*components)));

    va_list ap;
    va_start(ap, state);

    // TODO: finish this
    for (int i = va_arg(ap, int); i > -1; i = va_arg(ap, int)) {
        if (i >= state->component_type_count) {
            printf("trying to query component out of bounds. i = %i, type_count = %i\n", i,
                   state->component_type_count);
            exit(1);
        }

        components[component_type_count] = &state->components[i];
        component_indices[component_type_count] = i;

        component_type_count++;
    }
    va_end(ap);

    // Shrink the arrays to not waste memory
    component_indices = reallocarray(component_indices, component_type_count, sizeof(typeof(*component_indices)));
    components = reallocarray(components, component_type_count, sizeof(typeof(*components)));

    return (QueryResult){
        .component_type_count = component_type_count, .component_indices = component_indices, .components = components};
}

EntityQueryResult
get_entity_components(EcsState* const state, EntityId entity, ...)
{
    if (entity.id > state->entity_count) {
        printf("trying to query for an entity out of entity_count. id = %lu, entity_count = %lu\n", entity.id,
               state->entity_count);
        exit(1);
    }

    size_t component_type_count = 0;
    int* component_indices = calloc(state->component_type_count, sizeof(typeof(*component_indices)));
    GenericComponent* components = calloc(state->component_type_count, sizeof(typeof(*components)));

    va_list ap;
    va_start(ap, entity);

    for (int i = va_arg(ap, int); i > -1; i = va_arg(ap, int)) {
        if (i >= state->component_type_count) {
            printf("trying to query component out of bounds. i = %i, type_count = %i\n", i,
                   state->component_type_count);
            exit(1);
        }

        components[component_type_count] = (GenericComponent){
            .inner_size = state->components[i].element_size,
            .data = state->components[i].data[entity.id],
        };
        component_indices[component_type_count] = i;

        component_type_count++;
    }

    va_end(ap);

    component_indices = reallocarray(component_indices, component_type_count, sizeof(typeof(*component_indices)));
    components = reallocarray(components, component_type_count, sizeof(typeof(*components)));

    return (EntityQueryResult){
        .component_type_count = component_type_count, .component_indices = component_indices, .components = components};
}
