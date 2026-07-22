/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopez-l <plopez-l@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 13:22:18 by plopez-l          #+#    #+#             */
/*   Updated: 2026/06/19 15:56:32 by plopez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlstiter;
	t_list	*new_node;
	void	*content;
	t_list	*aux;

	if (!lst || !f || !del)
		return (NULL);
	newlstiter = NULL;
	aux = lst;
	while (aux)
	{
		content = f(aux->content);
		new_node = ft_lstnew(content);
		if (!new_node)
		{
			del(content);
			ft_lstclear(&newlstiter, del);
			return (NULL);
		}
		ft_lstadd_back(&newlstiter, new_node);
		aux = aux->next;
	}
	return (newlstiter);
}
