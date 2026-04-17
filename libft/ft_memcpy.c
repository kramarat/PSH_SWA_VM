/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kramarat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 13:14:21 by kramarat          #+#    #+#             */
/*   Updated: 2026/01/24 13:16:06 by kramarat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*ptr_dest;

	if (dest == NULL && src == NULL)
		return (NULL);
	ptr_dest = (unsigned char *)dest;
	while (n--)
		*ptr_dest++ = *((const unsigned char *)src++);
	return (dest);
}
/*
int	main(void)
{
	//memcpy
	char	src1[] = "cinco";
	char	dest1[100];
	memcpy(dest1, src1, 6);
	printf("memcpy\nsrc: %s\ndest: %s\n\n", src1, dest1);

	//ft_memcpy
	char	src2[] = "cinco";
	char	dest2[100];
	ft_memcpy(dest2, src2, 6);
	printf("ft_memcpy\nsrc: %s\ndest: %s\n", src2, dest2);
}*/
