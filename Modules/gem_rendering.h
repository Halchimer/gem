#ifndef _GEM_RENDERING_F
#define _GEM_RENDERING_F

#include "../gem_module.h"

void gem_rendering_setup();

typedef struct
{

} gem_rendering;
gem_impl(gem_rendering, gem_module, .setup=&gem_rendering_setup);

#endif
