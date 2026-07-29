/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopez-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 13:32:05 by plopez-l          #+#    #+#             */
/*   Updated: 2026/07/28 13:32:12 by plopez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	*get_numbers(int argc, char **argv, int *flag_coun, int *count)
{
	int	*numbers;

	numbers = malloc(sizeof(int) * compute_max_size(argc, argv));
	if (!numbers)
		return (NULL);
	*count = parse_all_args(argc, argv, flag_coun, numbers);
	return (numbers);
}

void	validate_numbers(int *flag_coun, int *numbers, int count)
{
	if (has_conflict(flag_coun) || has_duplicates(numbers, count))
	{
		free(numbers);
		error_exit();
	}
}

t_stack	*prepare_stack(int *numbers, int count)
{
	t_stack	*a;

	numbers = psindex(numbers, count);
	if (!numbers && count > 0)
		error_exit();
	a = build_list(numbers, count);
	free(numbers);
	if (!a && count > 0)
		error_exit();
	return (a);
}

int	parse_all_args(int argc, char **argv, int *flag_coun, int *numbers)
{
	int		i;
	int		count;
	char	**nbr_strs;

	count = 0;
	i = 1;
	while (i < argc)
	{
		nbr_strs = ft_split(argv[i], ' ');
		parse_tokens(nbr_strs, flag_coun, numbers, &count);
		free_split(nbr_strs);
		i++;
	}
	return (count);
}

int	main(int argc, char **argv)
{
	int		flag_coun[5];
	int		*numbers;
	int		count;
	t_stack	*a;
	double	dis;

	if (argc < 2)
		return (0);
	ft_init_flags(flag_coun);
	numbers = get_numbers(argc, argv, flag_coun, &count);
	if (!numbers)
		return (1);
	validate_numbers(flag_coun, numbers, count);
	a = prepare_stack(numbers, count);
	dis = list_disorder(a);
	if (count > 1)
	{
		if (flag_coun[4] > 0)
			print_bench(flag_coun, dis, execute_sort(&a, count,
				choose_strategy(flag_coun, dis), flag_coun));
		else
			free(execute_sort(&a, count, 
				choose_strategy(flag_coun, dis), flag_coun));
	}
	free_stack(a);
	return (0);
}
