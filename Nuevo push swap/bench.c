#include "push_swap.h"

void	print_bench(int *flags, double dis, int total)
{
	int			strategy;
	const char	*name;
	const char	*complexity;
	char		*total_str;

	strategy = choose_strategy(flags, dis);
	total_str = ft_itoa(total);
	if (!total_str)
		return ;
	name = strategy_name(strategy);
	complexity = strategy_complexity(strategy);
	write(2, name, ft_strlen(name));
	write(2, " - ", 3);
	write(2, complexity, ft_strlen(complexity));
	write(2, " - ", 3);
	write(2, total_str, ft_strlen(total_str));
	write(2, "\n", 1);
	free(total_str);
}
