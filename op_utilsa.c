/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_utilsa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiesan <javiesan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/29 15:17:03 by javiesan          #+#    #+#             */
/*   Updated: 2026/07/30 12:35:03 by plopez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	op_swap_a(t_stack *a, int *op_count)
{
	swap_a(a);
	op_count[OP_SA]++;
}

void	op_swap_b(t_stack *b, int *op_count)
{
	swap_b(b);
	op_count[OP_SB]++;
}

void	op_push_a(t_stack **a, t_stack **b, int *op_count)
{
	pa(a, b);
	op_count[OP_PA]++;
}

void	op_push_b(t_stack **a, t_stack **b, int *op_count)
{
	pb(a, b);
	op_count[OP_PB]++;
}
