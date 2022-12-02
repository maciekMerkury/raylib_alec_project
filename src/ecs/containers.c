#include "containers.h"
#include <stdio.h>
#include <stdlib.h>

// FIXME: This function is quite unsafe, as it relies purely on the assumption that element_i will refer to a living entity
void*
get_element(CompactContainer* const container, size_t element_i)
{
    if (element_i >= container->cap) {
        printf("trying to get element grater than capacity. element_i: %lu, cap: %lu", element_i, container->cap);
        exit(1);
    }

    // convertion to char* is required, as pointer arithmetics on void* are not allowed
    return (char*)container->data + element_i * container->element_size;
}
