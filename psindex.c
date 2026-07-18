/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   psindex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiesan <javiesan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 21:26:25 by javiesan          #+#    #+#             */
/*   Updated: 2026/07/15 21:26:25 by javiesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int *psindex(int *cadena, int n)
{
    int i;
    int j;
    int position;
    int *result;

    i = 0;

    result = malloc(n * sizeof(int));
    while (i < n)
    {
        position = 0;
        j = 0;
        while (j < n)
        {
           if (cadena[j] < cadena[i])
                position++;
            j++;
        }
        result[i] = position + 1;
        i++;
    }
    return (result);
}

// int main(void)
// {
//     int i = 0;
//     int paraindexar[] = {4, 26, 3, -54, 2, 15, -84, 12, 1}; //6,9,5,2,4,8,1,7,3
//     int *resultadoindexado;
//     int n = 9;
    
//     resultadoindexado = psindex(paraindexar, n);

//     while (i < n)
//         printf("%i", resultadoindexado[i++]);
//     free (resultadoindexado);
//     return (0);
// }