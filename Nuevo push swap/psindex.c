/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   psindex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiesan <javiesan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 21:26:25 by javiesan          #+#    #+#             */
/*   Updated: 2026/07/24 13:49:36 by plopez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int *psindex(int *numbers, int count)
{
    int i;
    int j;
    int position;
    int *result;

    i = 0;

    result = malloc(count * sizeof(int));
	if (!result)
		return (0);
    while (i < count)
    {
        position = 0;
        j = 0;
        while (j < count)
        {
           if (numbers[j] < numbers[i])
                position++;
            j++;
        }
        result[i] = position + 1;
        i++;
    }
    free (numbers);
    return (result);
}
