/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kramarat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 12:26:06 by kramarat          #+#    #+#             */
/*   Updated: 2026/01/24 13:12:33 by kramarat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	while (n--)
		*ptr++ = (unsigned char) c;
	return (s);
}
/*int	main(void)
{
	char	str1[20] = "secret password ups";
	char	str2[20] = "secret password ups";

	//memset
	printf("%s\n", str1);
	memset(str1 + 7, '*', 8);
	printf("%s\n\n", str1);

	//ft_memset
	printf("%s\n", str2);
	ft_memset(str2 + 7, '*', 8);
	printf("%s\n", str2);
}*/
