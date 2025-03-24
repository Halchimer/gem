#include "gem_component.h"

inline struct gem_component_tree_node *gem_create_component_node(component_t data)
{
    return NEW(gem_component_tree_node, .c=data, .left=NULL, .right=NULL, .height=0);
}

struct gem_component_tree_node *gem_get_component_insert_leaf_node(struct gem_component_tree_node **node, component_t c)
{
    if((*node)->left==NULL && (*node)->right==NULL)
            return *node;

    if      ((*node)->left!=NULL && c.tc.entity < (*node)->c.tc.entity)
        return gem_get_component_insert_leaf_node(&((*node)->left), c);
    else if ((*node)->right!=NULL && c.tc.entity > (*node)->c.tc.entity)
        return gem_get_component_insert_leaf_node(&((*node)->right), c);
    else
        return NULL;
}

inline uint32_t gem_component_node_height(struct gem_component_tree_node *node)
{
    if(node == NULL)
        return 0;
    return node->height;
}
inline uint32_t gem_component_node_calc_height(struct gem_component_tree_node *node)
{
    return GEM_MAX(gem_component_node_height(node->left), gem_component_node_height(node->right))+1;
}
int8_t gem_component_tree_get_balance_factor(struct gem_component_tree_node *node)
{
    if(node==NULL)
        return 0;
    return gem_component_node_height(node->left) - gem_component_node_height(node->right);
}

struct gem_component_tree_node *gem_component_tree_left_rotate(struct gem_component_tree_node *node)
{
    if(node==NULL)
            return NULL;

    struct gem_component_tree_node *y = node->right;
    struct gem_component_tree_node *t = y->left;

    y->left         = node;
    node->right     = t;

    node->height    = gem_component_node_calc_height(node);
    y->height       = gem_component_node_calc_height(y);

    return y;
}
struct gem_component_tree_node *gem_component_tree_right_rotate(struct gem_component_tree_node *node)
{
    if(node==NULL)
        return NULL;

    struct gem_component_tree_node *x = node->left;
    struct gem_component_tree_node *t = x->right;

    x->right        = node;
    node->left      = t;

    node->height    = gem_component_node_calc_height(node);
    x->height       = gem_component_node_calc_height(x);

    return x;
}

void component_t_insert(struct gem_component_tree_node **node, component_t c)
{
    static struct gem_component_tree_node **_leaf_rebalance_child_node = NULL;

    if((*node)==NULL)
        goto insert;

    if      (c.tc.entity < (*node)->c.tc.entity)
        gem_get_component_insert_leaf_node(&((*node)->left), c);
    else if (c.tc.entity > (*node)->c.tc.entity)
        gem_get_component_insert_leaf_node(&((*node)->right), c);

    if(_leaf_rebalance_child_node == NULL)
        return;

    if(!((*node)->_balance_factor > -1 && (*node)->_balance_factor < 1))
        return;

    if(*_leaf_rebalance_child_node == (*node)->right) // the right subtree increases
    {
        if((*node)->_balance_factor < 0) // right-heavy -> balance factore decreases and < -1
        {
            if((*node)->c.tc.entity <= (*node)->right->c.tc.entity)
                gem_component_tree_right_rotate((*node)->right);
            gem_component_tree_left_rotate(*node);
            return;
        }
        if((*node)->_balance_factor >= 0) // left-heavy or balanced -> bf decreases
            (*node)->_balance_factor--;

        return;
    }
    // left increase

    if((*node)->_balance_factor > 0) // left-heavy -> bf > 1
    {
        if((*node)->c.tc.entity >= (*node)->left->c.tc.entity)
            gem_component_tree_left_rotate((*node)->left);

        gem_component_tree_right_rotate(*node);
        return;
    }
    if((*node)->_balance_factor <= 0) // right-heavy or balanced -> balance factor increases
        (*node)->_balance_factor++;

    return;
    insert : {
        *node = gem_create_component_node(c);
        **_leaf_rebalance_child_node = node;
    }
}


component_t *search(struct gem_component_tree_node **node, component_t c)
{
    return NULL;
}
