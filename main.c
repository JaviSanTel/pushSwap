/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiesan <javiesan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 13:32:05 by plopez-l          #+#    #+#             */
/*   Updated: 2026/08/03 18:59:41 by javiesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	*get_num(int argc, char **argv, int *flag_coun, int *count)
{
	int	*num;

	num = malloc(sizeof(int) * compute_max_size(argc, argv));
	if (!num)
		return (NULL);
	*count = parse_all_args(argc, argv, flag_coun, num);
	return (num);
}

void	validate_num(int *flag_coun, int *num, int count)
{
	if (has_conflict(flag_coun) || has_duplicates(num, count))
	{
		free(num);
		error_exit();
	}
}

t_stack	*prepare_stack(int *num, int count)
{
	t_stack	*a;

	num = psindex(num, count);
	if (!num && count > 0)
		error_exit();
	a = build_list(num, count);
	free(num);
	if (!a && count > 0)
		error_exit();
	return (a);
}

int	parse_all_args(int argc, char **argv, int *flag_coun, int *num)
{
	int		i;
	int		count;
	char	**nbr_strs;

	count = 0;
	i = 1;
	while (i < argc)
	{
		nbr_strs = ft_split(argv[i], ' ');
		parse_tokens(nbr_strs, flag_coun, num, &count);
		free_split(nbr_strs);
		i++;
	}
	return (count);
}

int	main(int argc, char **argv)
{
	int		flag_coun[5];
	int		*num;
	int		count;
	t_stack	*a;
	double	dis;

	if (argc < 2)
		return (0);
	ft_init_flags(flag_coun);
	num = get_num(argc, argv, flag_coun, &count);
	if (!num)
		return (1);
	validate_num(flag_coun, num, count);
	a = prepare_stack(num, count);
	dis = list_disorder(a);
	run_and_output(&a, flag_coun, count, dis);
	free_stack (a);
	return (0);
}
