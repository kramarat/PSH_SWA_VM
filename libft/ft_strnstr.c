/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kramarat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 14:09:53 by kramarat          #+#    #+#             */
/*   Updated: 2026/01/24 14:10:26 by kramarat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	int		i;
	size_t	little_len;

	little_len = ft_strlen(little);
	if (!little[0])
		return ((char *)big);
	i = 0;
	while (big[i] && little_len <= len - i)
	{
		if (!ft_strncmp(big + i, little, little_len))
			return ((char *)big + i);
		i++;
	}
	return (0);
}
/*
int	main(void)
{
	char	str[] = "to find a needle in a haystack";
	char	substr[] = "needle";
	int	n = 18;

	printf("ft_strnstr: %p\n", ft_strnstr(str, substr, n);
}*/
