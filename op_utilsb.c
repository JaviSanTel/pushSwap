/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_utilsb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiesan <javiesan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/29 15:15:20 by javiesan          #+#    #+#             */
/*   Updated: 2026/08/03 19:01:35 by javiesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	op_rotate_a(t_stack *a, int *op_count)
{
	rotate_a(a);
	op_count[OP_RA]++;
}

void	op_rotate_b(t_stack *b, int *op_count)
{
	rotate_b(b);
	op_count[OP_RB]++;
}

void	op_rev_rotate_a(t_stack *a, int *op_count)
{
	reverse_rotate_a(a);
	op_count[OP_RRA]++;
}

void	op_rev_rotate_b(t_stack *b, int *op_count)
{
	reverse_rotate_b(b);
	op_count[OP_RRB]++;
}
