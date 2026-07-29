/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopez-l <plopez-l@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 16:15:03 by plopez-l          #+#    #+#             */
/*   Updated: 2026/06/15 17:57:28 by plopez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*ptrns;
	size_t			slen;
	unsigned int	i;

	if (!s || !f)
		return (NULL);
	slen = ft_strlen(s);
	ptrns = (char *)malloc(sizeof (char) * slen + 1);
	if (ptrns == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		ptrns[i] = f(i, s[i]);
		i++;
	}
	ptrns[i] = '\0';
	return (ptrns);
}
