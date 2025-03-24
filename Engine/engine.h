#ifndef _GEM_H
#define _GEM_H

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include "gem_dyn_array.h"
#include "gem_dyn_bitset.h"
#include "gem_utils.h"
#include "gem_component.h"
#include "gem_module.h"
#include "entity.h"


/*
*   ECS parameters
*/

#ifndef MAX_ENTITIES
#define MAX_ENTITIES 100000
#endif

/*
*   ECS
*/

/*
*   Event handler (deprecated)
*/

typedef void gem_callback(entity_t e, void* args);

struct gem_event_handler_deprecated
{
    void (**callbacks)(entity_t e, void* args);
    uint32_t bindings;
};

[[deprecated]]
inline void gem_bind(struct gem_event_handler_deprecated *ev, void (*callback)(entity_t e, void* args))
{
    if(ev->callbacks == nullptr)
        ev->callbacks = (gem_callback**)calloc(1, sizeof(gem_callback*));
    else
        ev->callbacks = (gem_callback**)realloc(ev->callbacks, sizeof(gem_callback*) * (ev->bindings+1));
    ev->callbacks[ev->bindings] = callback;
    ev->bindings++;
}

[[deprecated]]
inline void gem_free_event_handler(struct gem_event_handler_deprecated *ev)
{
    free(ev->callbacks);
}

[[deprecated]]
inline void gem_invoke(struct gem_event_handler_deprecated *ev, entity_t sender, void* args)
{
    for(int i=0; i<ev->bindings; i++)
        ev->callbacks[i](sender, args);
}

struct gem_inst;
typedef void system_t(struct gem_inst* inst);

typedef struct
{
    system_t* systems;
}schedule_t;

typedef struct gem_inst // represents a single instance of the ecs, holding entities, their components and systems.
{
    bool _is_running;

    entity_signature_t entity_arr[MAX_ENTITIES];
    uint32_t entity_count;
    uint32_t _last_free_entity_index;

    uint8_t module_count;
    gem_module *modules;

    struct gem_component_tree_node comp_table[SIGNATURE_BIT_SIZE];
} gem_inst_t;

struct gem_inst* gem_current_inst(struct gem_inst *inst);

bool has_component(entity_t e, uint32_t c_id);

component_t* add_component(entity_t e, component_t c);

/// spawns an entity in the world with the set of components provided
/// @ args    : components,
/// @ returns : Entity's id. -1 => failed to spawn entity.
entity_t gem_spawn(component_t first, ...);


[[deprecated]]
inline void gem_invoke_schedule(struct gem_event_handler_deprecated *schedule)
{
    gem_invoke(schedule, -1, nullptr);
}

void gem_add_module(gem_module mod);

void gem_run();

void gem_quit();

#endif
