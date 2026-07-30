/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bench.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopez-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 13:31:11 by plopez-l          #+#    #+#             */
/*   Updated: 2026/07/30 13:31:29 by plopez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	total_from_counts(int *op_counts)
{
	int	i;
	int	total;

	i = 0;
	total = 0;
	while (i < 11)
		total += op_counts[i++];
	return (total);
}

void	print_percentage(double dis)
{
	int		scaled;
	int		whole;
	char	*whole_str;
	char	*frac_str;

	scaled = (int)(dis * 10000 + 0.5);
	whole = scaled / 100;
	whole_str = ft_itoa(whole);
	frac_str = ft_itoa(scaled % 100);
	if (!whole_str || !frac_str)
	{
		free(whole_str);
		free(frac_str);
		return ;
	}
	write(2, "[bench] disorder: ", 18);
	write(2, whole_str, ft_strlen(whole_str));
	write(2, ".", 1);
	if (scaled % 100 < 10)
		write(2, "0", 1);
	write(2, frac_str, ft_strlen(frac_str));
	write(2, "%\n", 2);
	free(whole_str);
	free(frac_str);
}

void	print_strategy_line(int *flags, int strategy, int total)
{
	const char	*name;
	const char	*complexity;
	char		*total_str;

	if (strategy_forced(flags))
		name = strategy_name(strategy);
	else
		name = "Adaptive";
	complexity = strategy_complexity(strategy);
	total_str = ft_itoa(total);
	if (!total_str)
		return ;
	write(2, "[bench] strategy: ", 18);
	write(2, name, ft_strlen(name));
	write(2, " / ", 3);
	write(2, complexity, ft_strlen(complexity));
	write(2, "\n[bench] total_ops: ", 20);
	write(2, total_str, ft_strlen(total_str));
	write(2, "\n", 1);
	free(total_str);
}

void	print_breakdown(int *op_counts)
{
	int		i;
	char	*count_str;

	i = 0;
	write(2, "[bench] ", 8);
	while (i < 11)
	{
		count_str = ft_itoa(op_counts[i]);
		if (count_str)
		{
			write(2, op_name(i), ft_strlen(op_name(i)));
			write(2, ": ", 2);
			write(2, count_str, ft_strlen(count_str));
			free(count_str);
		}
		if (i == 4)
			write(2, "\n[bench] ", 9);
		else if (i < 10)
			write(2, " ", 1);
		i++;
	}
	write(2, "\n", 1);
}

void	print_bench(int *flags, double dis, int *op_counts)
{
	int	strategy;
	int	total;

	if (!op_counts)
		error_exit();
	print_percentage(dis);
	strategy = choose_strategy(flags, dis);
	total = total_from_counts(op_counts);
	print_strategy_line(flags, strategy, total);
	print_breakdown(op_counts);
	free(op_counts);
}
