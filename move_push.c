/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_push.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopez-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 16:22:35 by plopez-l          #+#    #+#             */
/*   Updated: 2026/07/22 16:26:41 by plopez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	push(t_stack **dest, t_stack **src)
{
	t_stack	*node;

	if (src == NULL || *src == NULL)
		return ;
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

int	pa(t_stack **a, t_stack **b)
{
	push(a, b);
	write(1, "pa\n", 3);
	return (1);
}

int	pb(t_stack **a, t_stack **b)
{
	push(b, a);
	write(1, "pb\n", 3);
	return (1);
}
