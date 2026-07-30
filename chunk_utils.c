/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiesan <javiesan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/27 22:01:19 by javiesan          #+#    #+#             */
/*   Updated: 2026/07/30 17:54:34 by plopez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_position(t_stack *x)
{
	int	i;
	int	max_pos;
	int	max_val;

	i = 0 ;
	max_pos = 0;
	max_val = x->content;
	while (x != NULL)
	{
		if (x->content > max_val)
		{
			max_val = x->content;
			max_pos = i;
		}
		x = x->next;
		i++;
	}
	return (max_pos);
}

int	ft_size_st(t_stack *x)
{
	int	n;

	n = 0;
	while (x != NULL)
	{
		n++;
		x = x->next;
	}
	return (n);
}
