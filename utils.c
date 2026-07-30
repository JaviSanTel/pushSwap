/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopez-l <plopez-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 14:15:33 by plopez-l          #+#    #+#             */
/*   Updated: 2026/07/30 17:45:18 by plopez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	error_exit(void)
{
	write(2, "Error\n", 6);
	exit(1);
}

void	free_split(char **arr)
{
	int	j;

	j = 0;
	while (arr[j])
		free(arr[j++]);
	free(arr);
}

void	free_all(char **nbr_strs, int *num)
{
	if (nbr_strs)
		free_split(nbr_strs);
	if (num)
		free(num);
}

int	has_duplicates(int *num, int count)
{
	int	i;
	int	j;

	i = 0;
	while (i < count)
	{
		j = i + 1;
		while (j < count)
		{
			if (num[i] == num[j])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	compute_max_size(int argc, char **argv)
{
	int	i;
	int	max_size;

	max_size = 0;
	i = 1;
	while (i < argc)
		max_size += ft_strlen(argv[i++]);
	return (max_size);
}
