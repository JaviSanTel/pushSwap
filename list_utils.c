/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopez-l <plopez-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 14:45:01 by plopez-l          #+#    #+#             */
/*   Updated: 2026/07/30 17:45:18 by plopez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_stack	*new_node(int value)
{
	t_stack	*node;

	node = malloc(sizeof(t_stack));
	if (!node)
		return (NULL);
	node->content = value;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

t_stack	*build_list(int *num, int count)
{
	t_stack	*head;
	t_stack	*last;
	t_stack	*node;
	int		i;

	head = NULL;
	last = NULL;
	i = 0;
	while (i < count)
	{
		node = new_node(num[i]);
		if (!node)
		{
			free_stack(head);
			return (NULL);
		}
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

void	free_stack(t_stack *a)
{
	t_stack	*next;

	while (a)
	{
		next = a->next;
		free(a);
		a = next;
	}
}
