/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_sort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiesan <javiesan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 19:22:54 by javiesan          #+#    #+#             */
/*   Updated: 2026/07/29 12:49:34 by javiesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	order_special(t_stack **a, int delay)
{
	int	top;
	int	mid;
	
	top = (*a)->content - delay;
	mid = ((*a)->next)->content - delay;
	if (top == 3)
		rotate_a(a);
	if (mid == 3)
		reverse_rotate_a(a);
	if (top == 2)
		swap_a(a);
}
void	special_sort(t_stack **a, t_stack **b, int count)
{
	int pos;
	int	delay;
	
	if (count == 2)
	{
		swap_a(a);
		return;
	}
	delay = count - 3;
	while (count > 3)
	{
		pos = find_min_position(a);
		rotate_to_top(a, pos, count);
		pb(a, b);
		count--;
	}
	order_special(a, delay);
	while (b)
		pa(a, b);
}
