/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_sort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiesan <javiesan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 13:20:40 by plopez-l          #+#    #+#             */
/*   Updated: 2026/07/31 21:30:06 by javiesan         ###   ########.fr       */
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
	return (op_counts);
}

void	run_and_output(t_stack **a, int *flags, int count, double dis)
{
	if (count <= 1 || dis == 0.0)
	{
		if (count > 1 && flags[4] > 0)
			print_bench(flags, dis, init_counts());
		return ;
	}
	if (flags[4] > 0)
		print_bench(flags, dis, execute_sort(a, count,
				choose_strategy(flags, dis), flags));
	else
		free(execute_sort(a, count,
				choose_strategy(flags, dis), flags));
}
