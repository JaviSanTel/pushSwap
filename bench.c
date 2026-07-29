/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bench.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopez-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 13:29:22 by plopez-l          #+#    #+#             */
/*   Updated: 2026/07/28 13:29:32 by plopez-l         ###   ########.fr       */
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
	write(2, "[bench] Disorder: ", 18);
	write(2, whole_str, ft_strlen(whole_str));
	write(2, ".", 1);
	if (scaled % 100 < 10)
		write(2, "0", 1);
	write(2, frac_str, ft_strlen(frac_str));
	write(2, "%\n", 2);
	free(whole_str);
	free(frac_str);
}

void	print_summary(const char *name, const char *complexity, char *total)
{
	write(2, "[bench] Strategy: ", 18);
	write(2, name, ft_strlen(name));
	write(2, " - ", 3);
	write(2, complexity, ft_strlen(complexity));
	write(2, "\n[bench] Total operations: ", 27);
	write(2, total, ft_strlen(total));
	write(2, "\n", 1);
}

void	print_breakdown(int *op_counts)
{
	int		i;
	char	*count_str;

	i = 0;
	while (i < 11)
	{
		count_str = ft_itoa(op_counts[i]);
		if (count_str)
		{
			write(2, op_name(i), ft_strlen(op_name(i)));
			write(2, ": ", 2);
			write(2, count_str, ft_strlen(count_str));
			write(2, "\n", 1);
			free(count_str);
		}
		i++;
	}
}

void	print_bench(int *flags, double dis, int *op_counts)
{
	int		strategy;
	int		total;
	char	*total_str;

	if (!op_counts)
		error_exit();
	print_percentage(dis);
	strategy = choose_strategy(flags, dis);
	total = total_from_counts(op_counts);
	total_str = ft_itoa(total);
	if (!total_str)
	{
		free(op_counts);
		return ;
	}
	print_summary(strategy_name(strategy), strategy_complexity(strategy),
			total_str);
	free(total_str);
	print_breakdown(op_counts);
	free(op_counts);
}
