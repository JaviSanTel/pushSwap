/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_rotate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopez-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 16:27:29 by plopez-l          #+#    #+#             */
/*   Updated: 2026/07/22 16:33:18 by plopez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rotate(t_stack *stack)
{
	t_stack	*aux;
	int		temp;

	if (stack == NULL || stack->next == NULL)
		return ;
	temp = stack->content;
	aux = stack;
	while (aux->next != NULL)
	{
		aux->content = aux->next->content;
		aux = aux->next;
	}
	aux->content = temp;
}

int	rotate_a(t_stack *stack)
{
	rotate(stack);
	write(1, "ra\n", 3);
	return (1);
}

int	rotate_b(t_stack *stack)
{
	rotate(stack);
	write(1, "rb\n", 3);
	return (1);
}

int	rotate_rr(t_stack *a, t_stack *b)
{
	rotate(a);
	rotate(b);
	write(1, "rr\n", 3);
	return (1);
}
