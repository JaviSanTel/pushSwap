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
		return (3);
	if (dis < 0.5)
		return (1);
	return (2);
}

int	*execute_sort(t_stack **a, int n, int strategy)
{
	t_stack	*b;
	int		*op_counts;
	int		i;

	b = NULL;
	op_counts = malloc(sizeof(int) * 11);
	if (!op_counts)
		return (NULL);
	i = 0;
	while (i < 11)
		op_counts[i++] = 0;
	if (strategy == 0)
		sort_simple(a, &b, n, op_counts);
	else if (strategy == 1)
		sort_chunk(a, &b, n, op_counts);
	else if (strategy == 2)
		sort_radix(a, &b, n, op_counts);
	else
		sort_near_sorted(a, &b, n, op_counts);
	return (op_counts);
}

const char	*strategy_name(int strategy)
{
	if (strategy == 0)
		return ("Simple");
	if (strategy == 1)
		return ("Chunk");
	if (strategy == 2)
		return ("Radix");
	return ("Near sorted");
}

const char	*strategy_complexity(int strategy)
{
	if (strategy == 0)
		return ("O(n^2)");
	if (strategy == 1)
		return ("O(n*sqrt(n))");
	if (strategy == 2)
		return ("O(n*log(n))");
	return ("O(n)");
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
