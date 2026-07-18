/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disorder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiesan <javiesan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/19 00:42:22 by javiesan          #+#    #+#             */
/*   Updated: 2026/07/19 00:42:22 by javiesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

double disorder(int *list, int n)
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
    while (i < n)
    {
        j = i + 1;
        while (j < n)
        {
            if (list[i] > list[j])
                dis++;
            j++;
            total++;
        }
        i++;
    }
    return (dis/total);
}
#include <stdio.h>
int main(void)
{
    int ordenada[]  = {1,2,3,4,5};
    int invertida[] = {5,4,3,2,1};
    int media[]     = {3,1,2};

    printf ("ordenada  (esperado 0)    -> %f\n", disorder(ordenada, 5));
    printf ("invertida (esperado 1)    -> %f\n", disorder(invertida, 5));
    printf ("media     (esperado 0.67) -> %f\n", disorder(media, 3));
    return (0);
}
