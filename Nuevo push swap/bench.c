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
	int			strategy;
	int			total;
	const char	*name;
	const char	*complexity;
	char		*total_str;

	if (!op_counts)
		error_exit();
	strategy = choose_strategy(flags, dis);
	total = total_from_counts(op_counts);
	total_str = ft_itoa(total);
	if (!total_str)
	{
		free(op_counts);
		return ;
	}
	name = strategy_name(strategy);
	complexity = strategy_complexity(strategy);
	write(2, name, ft_strlen(name));
	write(2, " - ", 3);
	write(2, complexity, ft_strlen(complexity));
	write(2, " - ", 3);
	write(2, total_str, ft_strlen(total_str));
	write(2, "\n", 1);
	free(total_str);
	print_breakdown(op_counts);
	free(op_counts);
}
