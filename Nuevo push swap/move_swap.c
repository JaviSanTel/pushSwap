/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopez-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 15:41:12 by plopez-l          #+#    #+#             */
/*   Updated: 2026/07/22 15:43:56 by plopez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	swap(t_stack *stack)
{
	t_stack	*aux;
	int		tmp;

	aux = stack;
	if (aux != NULL && aux->next != NULL)
	{
		tmp = aux->content;
		aux->content = aux->next->content;
		aux->next->content = tmp;
	}
}

int	swap_a(t_stack *stack)
{
	swap(stack);
	write(1, "sa\n", 3);
	return (1);
}

int	swap_b(t_stack *stack)
{
	swap(stack);
	write(1, "sb\n", 3);
	return (1);
}

int	swap_ss(t_stack *a, t_stack *b)
{
	swap(a);
	swap(b);
	write(1, "ss\n", 3);
	return (1);
}
