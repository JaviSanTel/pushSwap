/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radix.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiesan <javiesan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/26 19:59:13 by javiesan          #+#    #+#             */
/*   Updated: 2026/07/29 10:05:00 by javiesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_radix(t_stack **a, t_stack **b, int n)
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
				rotate_a(*a);
			else
				pb(a, b);
			i++;
		}
		while (*b)
			pa(a, b);
		bit++;
	}
}
