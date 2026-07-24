/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disorder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiesan <javiesan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/19 00:42:22 by javiesan          #+#    #+#             */
/*   Updated: 2026/07/24 14:00:42 by plopez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

double disorder(int *numbers, int count)
{
    int i;
    int j;
    double dis;
    double total;

    if (n <= 1)
        return (0);
    dis = 0;
    total = 0;
    i = 0;
    while (i < count)
    {
        j = i + 1;
        while (j < count)
        {
            if (numbers[i] > numbers[j])
                dis++;
            j++;
            total++;
        }
        i++;
    }
    return (dis/total)
}
