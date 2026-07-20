

#include "push_swap.h"

void push(t_list **dest, t_list **src)
{
    t_list *node;

    if (src == NULL || *src == NULL)
        return;
    node = *src;
    *src = node->next;
    if (*src != NULL)
        (*src)->prev = NULL;
    node->next = *dest;
    node->prev = NULL;
    if (*dest != NULL)
        (*dest)->prev = node;
    *dest = node;
}

int pa(t_list **a, t_list **b)
{
    push(a, b);
    write(1, "pa\n", 3);
    return (1);
}

int pb(t_list **a, t_list **b)
{
    push(b, a);
    write(1, "pb\n", 3);
    return (1);
}
