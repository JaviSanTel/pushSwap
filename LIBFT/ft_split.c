/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopez-l <plopez-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 11:13:17 by plopez-l          #+#    #+#             */
/*   Updated: 2026/06/18 17:07:57 by plopez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_words(char const *s, char c)
{
	size_t	count;
	int		in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c && in_word == 0)
		{
			in_word = 1;
			count++;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (count);
}

static void	*ft_free_split(char **split, size_t i)
{
	while (i > 0)
	{
		i--;
		free (split[i]);
	}
	free (split);
	return (NULL);
}

static size_t	ft_get_word_len(const char *s, char c)
{
	size_t	len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	return (len);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	size_t	i;
	size_t	word_len;

	if (!s)
		return (NULL);
	split = (char **)malloc(sizeof(char *) * (ft_count_words(s, c) + 1));
	if (!split)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s)
		{
			word_len = ft_get_word_len(s, c);
			split[i] = ft_substr(s, 0, word_len);
			if (!split[i++])
				return (ft_free_split(split, i - 1));
			s += word_len;
		}
	}
	split[i] = NULL;
	return (split);
}
