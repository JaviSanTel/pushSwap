/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopez-l <plopez-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 18:09:48 by plopez-l          #+#    #+#             */
/*   Updated: 2026/06/17 18:08:31 by plopez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t		i;
	char		*src;

	i = 0;
	src = (char *)s;
	c = (char)c;
	while (src[i] != '\0')
		i++;
	while (i > 0)
	{
		if (src[i] == c)
			return (&src[i]);
		i--;
	}
	if (src[i] == c)
		return (&src[i]);
	return (NULL);
}
