/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopez-l <plopez-l@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 15:12:00 by plopez-l          #+#    #+#             */
/*   Updated: 2026/06/10 12:06:31 by plopez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptrns;
	size_t	i;
	size_t	slen;

	if (!s)
		return (NULL);
	slen = 0;
	slen = ft_strlen(s);
	if (start >= slen)
		slen = 0;
	else if (slen - start < len)
		slen = slen - start;
	else
		slen = len;
	ptrns = (char *)malloc(sizeof(char) * (slen + 1));
	if (ptrns == NULL)
		return (NULL);
	i = 0;
	while (i < slen)
	{
		ptrns[i] = s[start + i];
		i++;
	}
	ptrns[i] = '\0';
	return (ptrns);
}
