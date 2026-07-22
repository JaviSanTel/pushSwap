/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopez-l <plopez-l@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 17:41:46 by plopez-l          #+#    #+#             */
/*   Updated: 2026/06/17 17:15:17 by plopez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	char	*src;

	src = (char *)s;
	i = 0;
	c = (char)c;
	while (src[i] != '\0')
	{
		if (src[i] == c)
			return (&src[i]);
		i++;
	}
	if (c == '\0')
		return (&src[i]);
	return (NULL);
}
