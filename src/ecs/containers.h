#pragma once

#include <stddef.h>

/// To be used with components commonly used by entities
typedef struct {
    /// The size of a singular component held by this container
    size_t element_size;

    /// The maximum number of elements that can fit in the currently allocated memory
    size_t cap;

    /// The array holding the components.
    /// Its size == element_size * cap
    void* data;

} CompactContainer;

void* get_element(CompactContainer* const container, size_t element_i);
