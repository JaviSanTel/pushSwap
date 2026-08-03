/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_simple.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiesan <javiesan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 12:29:56 by plopez-l          #+#    #+#             */
/*   Updated: 2026/08/03 18:24:15 by javiesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	find_min_position(t_stack *a)
{
	t_stack	*node;
	int		min_val;
	int		min_pos;
	int		pos;

	node = a;
	min_val = a->content;
	min_pos = 0;
	pos = 0;
	while (node)
	{
		if (node->content < min_val)
		{
			min_val = node->content;
			min_pos = pos;
		}
		node = node->next;
		pos++;
	}
	return (min_pos);
}

void	rotate_to_top(t_stack *a, int pos, int size, int *op_counts)
{
	int	i;

	i = 0;
	if (pos <= size - pos)
	{
		while (i++ < pos)
			op_rotate_a(a, op_counts);
	}
	else
	{
		while (i++ < size - pos)
			op_rev_rotate_a(a, op_counts);
	}
}

void	sort_simple(t_stack **a, t_stack **b, int n, int *op_counts)
{
	int	i;
	int	pos;

	i = 0;
	while (i < n)
	{
		pos = find_min_position(*a);
		rotate_to_top(*a, pos, n - i, op_counts);
		op_push_b(a, b, op_counts);
		i++;
	}
	i = 0;
	while (i < n)
	{
		op_push_a(a, b, op_counts);
		i++;
	}
}
