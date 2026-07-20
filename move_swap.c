#include "push_swap.h"

void swap(t_list *stack)
{
    t_list  *aux;
    int     tmp;

    aux = stack;
    if (aux != NULL && aux->next != NULL)
    {
        tmp = aux->content;
        aux->content = aux->next->content;
        aux->next->content = tmp;
    }
}

int swap_a(t_list *stack)
{
    swap(stack);
    write(1, "sa\n", 3);
    return (1);
}

int swap_b(t_list *stack)
{
    swap(stack);
    write(1, "sb\n", 3);
    return (1);
}

int swap_ss(t_list *a, t_list *b)
{
    swap(a);
    swap(b);
    write(1, "ss\n", 3);
    return (1);
}
