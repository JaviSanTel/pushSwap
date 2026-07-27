/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_simple.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopez-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 14:49:46 by plopez-l          #+#    #+#             */
/*   Updated: 2026/07/22 14:54:58 by plopez-l         ###   ########.fr       */
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

void	rotate_to_top(t_stack *a, int pos, int size, int *total_ops)
{
	int	i;

	i = 0;
	if (pos <= size - pos)
	{
		while (i++ < pos)
		{
			rotate_a(a);
			(*total_ops)++;
		}
	}
	else
	{
		while (i++ < size - pos)
		{
			reverse_rotate_a(a);
			(*total_ops)++;
		}
	}
}

void	sort_simple(t_stack **a, t_stack **b, int n, int *total_ops)
{
	int	i;
	int	pos;

	i = 0;
	while (i < n)
	{
		pos = find_min_position(*a);
		rotate_to_top(*a, pos, n - i, total_ops);
		pb(a, b);
		(*total_ops)++;
		i++;
	}
	i = 0;
	while (i < n)
	{
		pa(a, b);
		(*total_ops)++;
		i++;
	}
}
