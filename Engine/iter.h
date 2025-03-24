#ifndef _GEM_ITER_H
#define _GEM_ITER_H

#include "gem_utils.h"
#include <stdint.h>

/*
    GEM iter trait that can be implemented to many data types.
    Included in GEM arrays, component trees and so on...
*/

typedef struct
{
    void* (*next)();
    void *value;
    uint32_t index;
} gem_trait(iter_t);

#endif
