/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valmoral <valmoral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 00:00:00 by valmoral          #+#    #+#             */
/*   Updated: 2026/04/09 21:31:42 by valmoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	count_words(const char *s, char sep)
{
	int	count;

	count = 0;
	while (*s)
	{
		while (*s == sep)
			s++;
		if (*s)
		{
			count++;
			while (*s && *s != sep)
				s++;
		}
	}
	return (count);
}

static void	free_words(char **words, int used)
{
	while (used > 0)
		free(words[--used]);
	free(words);
}

static char	*copy_word(const char *start, int len)
{
	char	*word;
	int		index;

	word = malloc((len + 1) * sizeof(char));
	if (!word)
		return (NULL);
	index = 0;
	while (index < len)
	{
		word[index] = start[index];
		index++;
	}
	word[index] = '\0';
	return (word);
}

char	**ft_split(char const *s, char sep)
{
	char		**words;
	int			word_count;
	int			index;
	const char	*start;

	if (!s)
		return (NULL);
	word_count = count_words(s, sep);
	words = malloc((word_count + 1) * sizeof(char *));
	if (!words)
		return (NULL);
	index = 0;
	while (*s)
	{
		while (*s == sep)
			s++;
		start = s;
		while (*s && *s != sep)
			s++;
		if (s > start)
		{
			words[index] = copy_word(start, (int)(s - start));
			if (!words[index++])
				return (free_words(words, index - 1), NULL);
		}
	}
	words[index] = NULL;
	return (words);
}
