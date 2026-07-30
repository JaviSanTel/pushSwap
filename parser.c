/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopez-l <plopez-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 14:22:16 by plopez-l          #+#    #+#             */
/*   Updated: 2026/07/30 17:45:18 by plopez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	is_valid_number(const char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (str[i] == '\0')
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	str_equals(const char *a, const char *b)
{
	int	i;

	i = 0;
	while (a[i] && b[i] && a[i] == b[i])
		i++;
	return (a[i] - b[i]);
}

long	str_to_long(const char *str)
{
	long	num;
	int		sign;
	int		i;

	num = 0;
	sign = 1;
	i = 0;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i])
		num = num * 10 + (str[i++] - '0');
	return (num * sign);
}

void	store_number(char *str, int *num, int *count, char **nbr_strs)
{
	long	value;

	if (!is_valid_number(str))
	{
		free_all(nbr_strs, num);
		error_exit();
	}
	value = str_to_long(str);
	if (value > INT_MAX || value < INT_MIN)
	{
		free_all(nbr_strs, num);
		error_exit();
	}
	num[*count] = (int)value;
	(*count)++;
}

void	parse_tokens(char **nbr_strs, int *flag_coun, int *num, int *count)
{
	int	j;
	int	type;

	j = 0;
	while (nbr_strs[j] != NULL)
	{
		type = get_flag_type(nbr_strs[j]);
		if (type != 0)
			flag_coun[type - 1]++;
		else
			store_number(nbr_strs[j], num, count, nbr_strs);
		j++;
	}
}
