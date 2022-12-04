#include "containers.h"
#include <stdio.h>
#include <stdlib.h>

// FIXME: This function is quite unsafe, as it relies purely on the assumption that element_i will refer to a living entity
GenericComponent
get_element(CompactContainer* const container, size_t element_i)
{
    // TODO: think of a way of handling that maybe
    /*
    if (element_i >= container->cap) {
        printf("trying to get element grater than capacity. element_i: %lu, cap: %lu", element_i, container->cap);
        exit(1);
    }
    */

    GenericComponent comp = {
        .inner_size = container->element_size,
        .data = container->data[element_i]
    };

    return comp;
}
