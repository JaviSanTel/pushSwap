/* ************************************************************************** */
/* */
/* :::      ::::::::   */
/* push_swap3.c                                    :+:      :+:    :+:    */
/* +:+ +:+         +:+     */
/* By: casa <marvin@42.fr>                         +#+  +:+       +#+         */
/* +#+#+#+#+#+   +#+           */
/* Created: 2026/07/19 19:35:23 by casa          #+#    #+#             */
/* Updated: 2026/07/19 20:12:26 by casa         ###   ########.fr        */
/* */
/* ************************************************************************** */

#include "push_swap.h"

int is_valid_number(const char *str)
{
    int i;

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

int str_equals(const char *a, const char *b)
{
    int i;

    i = 0;
    while (a[i] && b[i] && a[i] == b[i])
        i++;
    return (a[i] - b[i]);
}

int get_flag_type(const char *str)
{
    if (str_equals(str, "--simple") == 0)
        return (1);
    if (str_equals(str, "--medium") == 0)
        return (2);
    if (str_equals(str, "--complex") == 0)
        return (3);
    if (str_equals(str, "--adaptive") == 0)
        return (4);
    if (str_equals(str, "--bench") == 0)
        return (5);
    return (0);
}

int has_conflict(int *counts)
{
    int total;
    int i;

    total = 0;
    i = 0;
    while (i < 4)
    {
        if (counts[i] > 0)
            total++;
        i++;
    }
    return (total > 1);
}

void error_exit(void)
{
    write(2, "Error\n", 6);
    exit(1);
}

void free_all(char **nbr_strs, int *numbers)
{
    int j;
str_to_checked_int
    if (nbr_strs)
    {
        j = 0;
        while (nbr_strs[j])
            free(nbr_strs[j++]);
        free(nbr_strs);
    }
    if (numbers)
        free(numbers);
}

long str_to_checked_int(const char *str)
{
    long    num;
    int     sign;
    int     i;

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
    {
        num = num * 10 + (str[i] - '0');
        i++;
    }
    return (num * sign);
}

int has_duplicates(int *numbers, int count)
{
    int i;
    int j;

    i = 0;
    while (i < count)
    {
        j = i + 1;
        while (j < count)
        {
            if (numbers[i] == numbers[j])
                return (1);
            j++;
        }
        i++;
    }
    return (0);
}

int main(int argc, char **argv)
{
    int     i;
    int     j;
    int     count;
    int     max_size;
    char    **nbr_strs;
    int     *numbers;
    int     flag_counts[5];
    int     type;
    long    value;

    if (argc < 2)
        return (0);
    i = 0;
    while (i < 5)
        flag_counts[i++] = 0;
    max_size = 0;
    i = 1;
    while (i < argc)
    {
        max_size = max_size + ft_strlen(argv[i]);
        i++;
    }
    numbers = malloc(sizeof(int) * max_size);
    if (!numbers)
        return (1);
    count = 0;
    i = 1;
    while (i < argc)
    {
	nbr_strs = ft_split(argv[i], ' ');
        j = 0;
        while (nbr_strs[j] != NULL) 
	{
		type = get_flag_type(argv[i]);
        	if (type != 0)
            		flag_counts[type - 1]++;
        	else
        	{
                	if (!is_valid_number(nbr_strs[j]))
                	{
                    		free_all(nbr_strs, numbers);
                    		error_exit();
                	}
                	value = str_to_checked_int(nbr_strs[j]);
                	if (val > INT_MAX || val < INT_MIN)
                	{
                    		free_all(nbr_strs, numbers);
                    		error_exit();
                	}
               		numbers[count] = (int)value;
                	count++;
                }
		j++;
        }
        j = 0;
        while (nbr_strs[j])
            free(nbr_strs[j++]);
        free(nbr_strs);
        i++;
    }
    if (has_conflict(flag_counts))
    {
        free_all(NULL, numbers);
        error_exit();
    }
    if (has_duplicates(numbers, count))
    {
        free_all(NULL, numbers);
        error_exit();
    }
    free(numbers);
    return (0);
}
