/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_small.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopez-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 12:30:55 by plopez-l          #+#    #+#             */
/*   Updated: 2026/07/30 12:30:58 by plopez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_three(t_stack **a, t_stack **b, int *op_counts)
{
	sort_simple(a, b, 3, op_counts);
}

void	sort_four(t_stack **a, t_stack **b, int *op_counts)
{
	int	pos;

	pos = find_min_position(*a);
	rotate_to_top(*a, pos, 4, op_counts);
	pb(a, b);
	op_counts[OP_PB]++;
	sort_three(a, b, op_counts);
	pa(a, b);
	op_counts[OP_PA]++;
}

void	sort_five(t_stack **a, t_stack **b, int *op_counts)
{
	int	pos;

	pos = find_min_position(*a);
	rotate_to_top(*a, pos, 5, op_counts);
	pb(a, b);
	op_counts[OP_PB]++;
	sort_four(a, b, op_counts);
	pa(a, b);
	op_counts[OP_PA]++;
}
