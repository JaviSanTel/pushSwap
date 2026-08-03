/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_sort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiesan <javiesan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 19:22:54 by javiesan          #+#    #+#             */
/*   Updated: 2026/08/03 18:36:11 by javiesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	order_special(t_stack **a, int delay, int *op_counts)
{
	int	top;
	int	mid;

	top = (*a)->content - delay;
	mid = ((*a)->next)->content - delay;
	if (top == 1 && mid == 3)
	{
		op_rev_rotate_a(*a, op_counts);
		op_swap_a(*a, op_counts);
	}
	if (top == 2 && mid == 3)
		op_rev_rotate_a(*a, op_counts);
	if (top == 2 && mid == 1)
		op_swap_a(*a, op_counts);
	if (top == 3 && mid == 1)
		op_rotate_a(*a, op_counts);
	if (top == 3 && mid == 2)
	{
		op_swap_a(*a, op_counts);
		op_rev_rotate_a(*a, op_counts);
	}
}

void	special_sort(t_stack **a, t_stack **b, int count, int *op_counts)
{
	int	pos;
	int	delay;

	if (count == 2)
		op_swap_a(*a, op_counts);
	delay = count - 3;
	while (count > 3)
	{
		pos = find_min_position(*a);
		rotate_to_top(*a, pos, count, op_counts);
		op_push_b(a, b, op_counts);
		count--;
	}
	if (count == 3)
		order_special(a, delay, op_counts);
	while (delay > 0 && delay--)
		op_push_a(a, b, op_counts);
}
