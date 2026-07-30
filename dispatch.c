/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopez-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 13:28:27 by plopez-l          #+#    #+#             */
/*   Updated: 2026/07/28 13:28:36 by plopez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	choose_strategy(int *flags, double dis)
{
	if (flags[0] > 0)
		return (0);
	if (flags[1] > 0)
		return (1);
	if (flags[2] > 0)
		return (2);
	if (dis < 0.2)
		return (0);
	if (dis < 0.5)
		return (1);
	return (2);
}

const char	*op_name(int index)
{
	if (index == OP_SA)
		return ("sa");
	if (index == OP_SB)
		return ("sb");
        if (index == OP_SS)
                return ("ss");
        if (index == OP_PA)
                return ("pa");
        if (index == OP_PB)
                return ("pb");
        if (index == OP_RA)
                return ("ra");
        if (index == OP_RB)
                return ("rb");
        if (index == OP_RR)
                return ("rr");
        if (index == OP_RRA)
                return ("rra");
        if (index == OP_RRB)
                return ("rrb");
        return ("rrr");
}

const char	*strategy_name(int strategy)
{
	if (strategy == 0)
		return ("Simple");
	if (strategy == 1)
		return ("Chunk");
	return ("Radix");
}

const char	*strategy_complexity(int strategy)
{
	if (strategy == 0)
		return ("O(n²)");
	if (strategy == 1)
		return ("O(n√n)");
	return ("O(n log n)");
}

double	list_disorder(t_stack *a)
{
	t_stack	*ni;
	t_stack	*nj;
	double	dis;
	double	total;

	if (a == NULL || a->next == NULL)
		return (0);
	dis = 0;
	total = 0;
	ni = a;
	while (ni)
	{
		nj = ni->next;
		while (nj)
		{
			if (ni->content > nj->content)
				dis++;
			total++;
			nj = nj->next;
		}
		ni = ni->next;
	}
	return (dis / total);
}
