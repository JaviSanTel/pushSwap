/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopez-l <plopez-l@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 18:41:10 by plopez-l          #+#    #+#             */
/*   Updated: 2026/06/15 17:45:27 by plopez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*destiny;
	unsigned char	*ptr;
	size_t			i;

	ptr = (unsigned char *)src;
	destiny = (unsigned char *)dest;
	i = 0;
	if (!ptr && !destiny)
		return (0);
	while (i < n)
	{
		destiny[i] = ptr[i];
		i++;
	}
	return (dest);
}
