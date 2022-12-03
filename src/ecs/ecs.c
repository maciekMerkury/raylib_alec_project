#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "ecs.h"

EcsState
ecs_init(size_t init_cap, ...)
{
    printf("penus works\n");
    EcsState state = {0};

    va_list ap;
    va_start(ap, init_cap);

    int i = 0;
    for (size_t size = va_arg(ap, size_t); size != 0; size = va_arg(ap, size_t)) {
        void* data = calloc(size, init_cap);
        if (!data) {
            printf("[%s; %d]:\tcould not malloc %lu bytes\n", __FILE__, __LINE__, size * init_cap);
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

QueryResult ecs_query(EcsState *const state, uint64_t mask)
{
}
