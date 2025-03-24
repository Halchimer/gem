#ifndef _GEM_STD_COMPONENTS
#define _GEM_STD_COMPONENTS

#include "../Engine/gem_component.h"
#include "../Engine/vector.h"

#define STDCOMP_ID_OFFSET 2 // Corresponds to the last standard component id.
// the developper must take this into account when setting ID for new components.

/*
*   TRANSFORM
*/

typedef struct gem_transform_component // transform system in 2d space (hence float for rotation.)
{
    vec3f64_t   position;
    float       rotation;
    vec2f_t     scale;
} transform_t;
gem_impl(transform_t, component_t, .id=1);

typedef struct{
    struct gem_transform_component *anchor;
} anchor_t;
gem_impl(anchor_t, component_t, .id=2, .dependencies=COMPSIG(transform_t));



#endif
