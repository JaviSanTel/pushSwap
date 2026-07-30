/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiesan <javiesan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/27 08:27:25 by javiesan          #+#    #+#             */
/*   Updated: 2026/07/30 08:17:16 by javiesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	isqrt(int n)
{
	int	i;

	i = 0;
	while ((i + 1) * (i + 1) <= n)
		i++;
	return (i);
}

void	found(t_stack **a, t_stack **b, t_chunkdata *data, int *op_count)
{
	int	found;
	int	t;
	int	mid;

	found = 0;
	mid = ((data->clow + (data->clow + data->csize - 1)) / 2);
	while (found < data->csize)
	{
		t = (*a)->content;
		if (data->clow <= t && t <= (data->clow + data->csize - 1))
		{
			if (t > mid)
				op_push_b(a, b, op_count);
			else
			{
				op_push_b(a, b, op_count);
				op_rotate_b(*b, op_count);
			}
			found ++;
		}
		else
			op_rotate_a(*a, op_count);
	}
}

void	push_chunk(t_stack **a, t_stack **b, int n, int *op_count)
{
	int	size;
	int	floor;
	int	step;
	t_chunkdata cdata;

	floor = isqrt(n);
	size = 3 * floor;
	step = (size - floor) / 7;
	cdata.clow = 1;
		while (cdata.clow <= n)
	{
		if (size > floor)
		{
			cdata.csize = size;
			size -= step;
		}
		else
			cdata.csize = floor;
		if (cdata.csize > n - cdata.clow + 1)
			cdata.csize = n - cdata.clow + 1;
		found(a, b, &cdata, op_count);
		cdata.clow += cdata.csize;
	}
}

void	return_global(t_stack **a, t_stack **b, int *op_count)
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
				op_rotate_b(*b, op_count);
		}
		else if (pos >= tam - pos)
		{
			total = tam - pos;
			while ((total--))
				op_rev_rotate_b(*b, op_count);
		}
		op_push_a(a, b, op_count);
	}
}

void	sort_chunk(t_stack **a, t_stack **b, int n, int *op_count)
{
	push_chunk(a, b, n, op_count);
	return_global(a, b, op_count);
}
