/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   psindex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiesan <javiesan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 21:26:25 by javiesan          #+#    #+#             */
/*   Updated: 2026/07/30 13:05:36 by plopez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	*psindex(int *num, int count)
{
	int	i;
	int	j;
	int	position;
	int	*result;

	i = 0;
	result = malloc(count * sizeof(int));
	if (!result)
	{
		free(num);
		return (NULL);
	}
	while (i < count)
	{
		position = 0;
		j = 0;
		while (j < count)
		{
			if (num[j] < num[i])
				position++;
			j++;
		}
		result[i] = position + 1;
		i++;
	}
	free(num);
	return (result);
}
