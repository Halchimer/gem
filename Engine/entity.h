#ifndef _GEM_ENTITY_H
#define _GEM_ENTITY_H

#include <stdint.h>

#ifndef SIGNATURE_BIT_SIZE
#define SIGNATURE_BIT_SIZE 64
#endif

typedef uint32_t entity_t;
typedef _BitInt (SIGNATURE_BIT_SIZE) entity_signature_t;

#endif
