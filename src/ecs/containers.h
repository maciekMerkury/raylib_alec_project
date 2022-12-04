#pragma once

#include <stddef.h>

/// To be used with components commonly used by entities
typedef struct {
    /// The size of a singular component held by this container
    size_t element_size;

    /// The array holding pointer the components.
    /// Its size == sizeof(any*) * cap
    void** data;
} CompactContainer;

typedef struct{
    size_t inner_size;
    void* data;
} GenericComponent;

/// Returns the pointer the component
GenericComponent get_element(CompactContainer* const container, size_t element_i);
