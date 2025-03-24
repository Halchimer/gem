#ifndef _GEM_COMPONENT_BIN_TREE_H
#define _GEM_COMPONENT_BIN_TREE_H

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include "gem_utils.h"
#include "entity.h"

/*
*   Const types
*/

#ifndef _COMP_ID_TYPE
#define _COMP_ID_TYPE uint8_t
#endif

// trait representing a component. implement it for a struct to make it a component.
typedef struct
{
    _COMP_ID_TYPE id;
    entity_signature_t dependencies; // Allows to make components that need others to work properly.
    entity_t entity;
} gem_trait(component_t);

struct gem_component_tree_node
{
    component_t c;
    struct gem_component_tree_node *right;
    struct gem_component_tree_node *left;
    int8_t _balance_factor : 2;
};

#define COMPSIG(C) (1 << C##_##component_t(&(C){}).tc.id)
#define DEP_UNION_2(C1, C2) (COMPSIG(C1) | COMPSIG(C2))
#define DEP_UNION_3(C1, C2, C3) (DEP_UNION_2(C1, C2) | COMPSIG(C3))
#define DEP_UNION_4(C1, C2, C3, C4) (DEP_UNION_3(C1, C2, C3) | COMPSIG(C4))
#define DEP_UNION_5(C1, C2, C3, C4, C5) (DEP_UNION_4(C1, C2, C3, C4) | COMPSIG(C5))

#define DEP_UNION_N_(N, ...) DEP_UNION_##N(__VA_ARGS__)
#define DEP_UNION(...) DEP_UNION_N_(PP_NARG(__VA_ARGS__), __VA_ARGS__)

void component_t_insert(struct gem_component_tree_node **node, component_t c);

void component_t_remove(struct gem_component_tree_node **node, uint32_t key);

component_t *search(struct gem_component_tree_node **node, component_t *c);

#endif
