/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopez-l <plopez-l@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 15:58:28 by plopez-l          #+#    #+#             */
/*   Updated: 2026/06/15 17:56:26 by plopez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptrns;
	size_t	s1len;
	size_t	s2len;

	if (!s1 || !s2)
		return (NULL);
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	ptrns = (char *)malloc(sizeof (char) * (s1len + s2len + 1));
	if (!ptrns)
		return (NULL);
	ft_strlcpy(ptrns, s1, s1len + 1);
	ft_strlcat(ptrns, s2, s1len + s2len + 1);
	return (ptrns);
}
