#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "containers.h"
#include "ecs.h"
#include "entity_id.h"
#include "queue.h"

#define REALLOC_INCREASE 8

EcsState
ecs_init(size_t init_cap, ...)
{
    EcsState state = {0};

    va_list ap;
    va_start(ap, init_cap);

    int i = 0;
    for (size_t size = va_arg(ap, size_t); size != 0; size = va_arg(ap, size_t)) {
        void** data = calloc(sizeof(void*), init_cap);
        if (!data) {
            printf("[%s; %d]:\tcould not malloc %lu bytes\n", __FILE__, __LINE__, sizeof(void*) * init_cap);
            perror("malloc error: ");
            exit(1);
        }

        state.components[i] = (CompactContainer){.element_size = size, .cap = init_cap, .data = data};

        if (++i >= MAXIMUM_COMPONENT_COUNT) {
            printf("No more than 64 component types are permitted, see ecs.h for more details\n");
            exit(1);
        }
    }

    state.component_type_count = i;

    va_end(ap);

    return state;
}

EntityId
init_entity(EcsState* const state, ...)
{
    EntityId id;

    if (is_empty(&state->empty_entity_queue)) {
        id = pop(&state->empty_entity_queue);
    } else {
        id = (EntityId){state->entity_count++};

        // increase the cap and realloc the array if needed
        for (int i = 0; i < state->component_type_count; ++i) {

            // increase in size is needed
            if (id.id > state->components[i].cap) {
                CompactContainer* cont = &state->components[i];

                cont->cap += REALLOC_INCREASE;

                void* new = reallocarray(cont->data, cont->cap, sizeof(void*));

                if (!new) {
                    printf("could not resize the component type %i. new size was supposed to be %lu\n", i, cont->cap);
                    exit(1);
                }

                cont->data = new;
            }
        }
    }

    /// set handles to null and free memory
    for (int i = 0; i < state->component_type_count; ++i) {
        free(get_element(&state->components[i], id.id));
        state->components[i].data[id.id] = NULL;
    }

    va_list ap;
    va_start(ap, state);

    for (int i = va_arg(ap, size_t); i != 0; i = va_arg(ap, size_t)) {
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
