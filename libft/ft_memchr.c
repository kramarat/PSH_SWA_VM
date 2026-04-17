/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kramarat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 14:02:32 by kramarat          #+#    #+#             */
/*   Updated: 2026/01/24 14:06:49 by kramarat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (ptr[i] == (unsigned char)c)
			return (&ptr[i]);
		i++;
	}
	return (NULL);
}
/*
int	main(void)
{
	char   *s = "quick brown fox jumps over the lazy dog";
	int   c = 'f';
	size_t   n = 17;

	printf("ft_memchr: %p\n", ft_memchr(s, c, n));
	printf("memchr: %p\n", memchr(s, c, n));
}*/
