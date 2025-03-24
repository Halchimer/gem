#ifndef _GEM_MODULE_F
#define _GEM_MODULE_F

#include "gem_utils.h"

typedef struct
{
    void (*setup)(void);
} gem_trait(gem_module);

#endif
