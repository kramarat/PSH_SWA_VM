/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kramarat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 18:47:11 by kramarat          #+#    #+#             */
/*   Updated: 2026/01/22 20:28:30 by kramarat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static char	**ft_free_all(char **array, int i)
{
	while (i > 0)
	{
		i--;
		free(array[i]);
	}
	free(array);
	return (NULL);
}

static int	word_count(char const *s, char c)
{
	int	count;
	int	in_word;

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

static int	word_len(char const *s, char c)
{
	int	len;

	len = 0;
	while (*(s + len) && *(s + len) != c)
		len++;
	return (len);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	int		i;
	int		words;

	if (!s)
		return (NULL);
	words = word_count(s, c);
	res = (char **)malloc(sizeof(char *) * (words + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (i < words)
	{
		while (*s == c)
			s++;
		res[i] = ft_substr(s, 0, word_len(s, c));
		if (!res[i])
			return (ft_free_all(res, i));
		s += word_len(s, c);
		i++;
	}
	res[i] = NULL;
	return (res);
}
