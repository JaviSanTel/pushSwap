/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radix.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiesan <javiesan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/26 19:59:13 by javiesan          #+#    #+#             */
/*   Updated: 2026/07/30 13:36:34 by plopez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_radix(t_stack **a, t_stack **b, int n, int *op_count)
{
	int	nbits;
	int	bit;
	int	i;

	nbits = 0;
	while ((1 << nbits) <= n)
		nbits++;
	bit = 0;
	while (bit < nbits)
	{
		i = 0;
		while (i < n)
		{
			if (((*a)->content >> bit) & 1)
				op_rotate_a(*a, op_count);
			else
				op_push_b(a, b, op_count);
			i++;
		}
		while (*b)
			op_push_a(a, b, op_count);
		bit++;
	}
}
