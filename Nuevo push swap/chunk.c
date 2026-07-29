/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiesan <javiesan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/27 08:27:25 by javiesan          #+#    #+#             */
/*   Updated: 2026/07/28 13:30:23 by javiesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	ft_isqrt(int n)
{
	int	i;

	i = 0;
	while ((i + 1) * (i + 1) <= n)
		i++;
	return (i);
}

void	ft_found(t_stack **a, t_stack **b, int low, int s)
{
	int	found;
	int	t;
	int	mid;

	found = 0;
	mid = ((low + (low + s - 1)) / 2);
	while (found < s)
	{
		t = (*a)->content;
		if (low <= t && t <= (low + s - 1))
		{
			if (t > mid)
				pb(a, b);
			else
			{
				pb(a, b);
				rotate_b(*b);
			}
			found ++;
		}
		else
			rotate_a(*a);
	}
}

void	ft_push_chunk(t_stack **a, t_stack **b, int n)
{
	int	size;
	int	floor;
	int	step;
	int	low;
	int	s;

	floor = ft_isqrt(n);
	size = 3 * floor;
	step = (size - floor) / 7;
	low = 1;
	while (low <= n)
	{
		if (size > floor)
		{
			s = size;
			size -= step;
		}
		else
			s = floor;
		if (s > n - low + 1)
			s = n - low + 1;
		ft_found(a, b, low, s);
		low += s;
	}
}

void	ft_return_global(t_stack **a, t_stack **b)
{
	int	pos;
	int	tam;
	int	total;

	while (*b != NULL)
	{
		pos = ft_position(*b);
		tam = ft_size_st(*b);
		if (pos <= tam - pos)
		{
			total = pos;
			while (total--)
				rotate_b(*b);
		}
		else if (pos >= tam - pos)
		{
			total = tam - pos;
			while ((total--))
				reverse_rotate_b(*b);
		}
		pa(a, b);
	}
}

void	ft_sort_chunk(t_stack **a, t_stack **b, int n)
{
	ft_push_chunk(a, b, n);
	ft_return_global(a, b);
}
