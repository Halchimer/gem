#include "engine.h"
#include "gem_component.h"
#include "gem_dyn_bitset.h"

struct gem_inst* gem_current_inst(struct gem_inst *inst)
{
    static struct gem_inst* sinst = NULL;
    if(inst!=NULL)
        sinst = inst;
    return sinst;
}

bool has_component(entity_t e, uint32_t c_id)
{
    struct gem_inst *inst = gem_current_inst(NULL);
    return bget(&(inst->entity_arr[e]), c_id);
}

component_t* add_component(entity_t e, component_t c)
{
    if(!has_component(e, c.tc.id))
        return NULL;

    struct gem_inst *inst = gem_current_inst(NULL);

    bset(&(inst->entity_arr[e]), c.tc.id, 1);

    // inst->comp_table[c.tc.id][e] = c; // TODO : pack components in the array at the begining -> no holes.

    return NULL;
}

entity_t gem_spawn(component_t first, ...)
{
    struct gem_inst *inst = gem_current_inst(NULL);

    if(inst->entity_count == MAX_ENTITIES)
        return -1;

    entity_t new_entity = inst->entity_count; // TODO : better way to get new index which handles holes in the array.

    inst->entity_arr[new_entity] = 0;

    add_component(new_entity, first);

    return -1;
}

void gem_add_module(gem_module mod)
{
    struct gem_inst *inst = gem_current_inst(NULL);

    if(inst->modules == NULL)
        inst->modules = (gem_module*)calloc(1, sizeof(gem_module));
    else
        inst->modules = (gem_module*)realloc(inst->modules, sizeof(gem_module) * (inst->module_count + 1));

    inst->modules[inst->module_count] = mod;
}

void gem_run()
{
    struct gem_inst *inst = gem_current_inst(NULL);

    inst->_is_running = true;

    while(inst->_is_running)
    {

    }
}

void gem_quit()
{
    struct gem_inst *inst = gem_current_inst(NULL);
    inst->_is_running = false;

    free(inst->modules);
}
