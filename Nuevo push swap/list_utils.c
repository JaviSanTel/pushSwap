/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopez-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 14:45:01 by plopez-l          #+#    #+#             */
/*   Updated: 2026/07/22 14:49:23 by plopez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_list	*new_node(int value)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->content = value;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

t_list	*build_list(int *numbers, int count)
{
	t_list	*head;
	t_list	*last;
	t_list	*node;
	int		i;

	head = NULL;
	last = NULL;
	i = 0;
	while (i < count)
	{
		node = new_node(numbers[i]);
		if (!node)
			return (NULL);
		else if (head == NULL)
			head = node;
		else
		{
			last->next = node;
			node->prev = last;
		}
		last = node;
		i++;
	}
	return (head);
}
