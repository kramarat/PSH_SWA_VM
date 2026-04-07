/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kramarat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 13:05:35 by kramarat          #+#    #+#             */
/*   Updated: 2026/01/24 13:06:40 by kramarat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	while (n--)
		*ptr++ = '\0';
}
/*
int	main(void)
{
        char    str1[16] = "testetesteteste";
        char    str2[16] = "testetesteteste";

        //bzero
        printf("%s\n", str1);
        bzero(str1 + 5, 10);
        printf("%s\n\n", str1);

        //ft_bzero
        printf("%s\n", str2);
        ft_bzero(str2 + 5, 10);
        printf("%s\n", str2);
}*/
