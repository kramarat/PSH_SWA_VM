/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kramarat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 12:05:31 by kramarat          #+#    #+#             */
/*   Updated: 2026/01/24 12:06:16 by kramarat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	if ((c >= 32) && (c <= 126))
		return (1);
	return (0);
}
/*
int	main(void)
{
	char	a = 32;
	char	b = 127;
	
	printf("isprint(a): %d\n", isprint(a));
	printf("ft_isprint(a): %d\n", ft_isprint(a));
	printf("isprint(b): %d\n", isprint(b));
	printf("ft_isprint(b): %d\n", ft_isprint(b));
}*/
