


#include "push_swap.h"

void reverse_rotate(t_list *stack)
{
    t_list  *aux;
    int     temp;

    if (stack == NULL || stack->next == NULL)
        return;
    aux = stack;
    while (aux->next != NULL)
        aux = aux->next;
    temp = aux->content;
    while (aux != stack)
    {
        aux->content = aux->prev->content;
        aux = aux->prev;
    }
    stack->content = temp;
}

int reverse_rotate_a(t_list *stack)
{
    reverse_rotate(stack);
    write(1, "rra\n", 4);
    return (1);
}

int reverse_rotate_b(t_list *stack)
{
    reverse_rotate(stack);
    write(1, "rrb\n", 4);
    return (1);
}

int reverse_rotate_rrr(t_list *a, t_list *b)
{
    reverse_rotate(a);
    reverse_rotate(b);
    write(1, "rrr\n", 4);
    return (1);
}
