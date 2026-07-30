/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_sort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopez-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 13:20:40 by plopez-l          #+#    #+#             */
/*   Updated: 2026/07/30 13:25:03 by plopez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	*init_counts(void)
{
	int	*op_counts;
	int	i;

	op_counts = malloc(sizeof(int) * 11);
	if (!op_counts)
		return (NULL);
	i = 0;
	while (i < 11)
		op_counts[i++] = 0;
	return (op_counts);
}

void	run_small_sort(t_stack **a, int n, int *op_counts)
{
	t_stack	*b;

	b = NULL;
	special_sort(a, &b, n, op_counts);
}

void	run_strategy_sort(t_stack **a, int n, int strategy, int *op_counts)
{
	t_stack	*b;

	b = NULL;
	if (strategy == 0)
		sort_simple(a, &b, n, op_counts);
	else if (strategy == 1)
		sort_chunk(a, &b, n, op_counts);
	else
		sort_radix(a, &b, n, op_counts);
}

int	*execute_sort(t_stack **a, int n, int strategy, int *flags)
{
	int	*op_counts;

	op_counts = init_counts();
	if (!op_counts)
		return (NULL);
	if (!strategy_forced(flags) && n >= 2 && n <= 5)
		run_small_sort(a, n, op_counts);
	else
		run_strategy_sort(a, n, strategy, op_counts);
	free_stack(*a);
	return (op_counts);
}
