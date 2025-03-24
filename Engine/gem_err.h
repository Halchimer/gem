#ifndef _GEM_ERR_H
#define _GEM_ERR_H

#include <stdio.h>
#include <stdint.h>
#include "gem_utils.h"

typedef struct
{
    void *obj;
    uint32_t err;
} gem_opt;

/*
*   GEM standard errors.
*/

typedef enum
{   // GEM_ERR_NONE -> if a function executes successfully it will throw this value. Used by gem's custom try catch system
    GEM_ERR_NONE                        = 0x100, //256 -> first byte reserved for user defined errors (255 ud errors possible)

    GEM_UNDEFINED_ERROR,                    // Self explanatory
    GEM_NULL_ENTITY_COMPONENT_INJECTION     // Thrown when the program tries to inject a component to a null entity.
}gem_std_err;

extern const char* _gem_enum_err_names[];

#define GEM_STD_ERR_MSG(E) fprintf(stderr, "%s at line %d" ,_gem_enum_err_names[E], __LINE__);

/*
*   GEM std err macros
*/

#define SOME(T, ...) (gem_opt){.obj = NEW(T, __VA_ARGS__), .err=GEM_ERR_NONE}
#define ERR(E) (gem_opt){.err = E, .obj=NULL}
#define UNWRAP(O, T) ({T _temp_unwrap_return_##__LINE__ = *((T*)O.obj); free(O.obj); _temp_unwrap_return_##__LINE__;})

#define TRY inline gem_opt _gem_try()
#define CATCH(E) if(_gem_try().err==E)
#define EXCEPT if(_gem_try().err!=GEM_ERR_NONE)
#define CATCHALL switch(_gem_try().err)


#endif
