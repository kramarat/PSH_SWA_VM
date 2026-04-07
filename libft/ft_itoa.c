/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kramarat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 17:24:28 by kramarat          #+#    #+#             */
/*   Updated: 2026/02/01 10:24:54 by kramarat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_intlen(long n)
{
	size_t	len;

	len = 0;
	if (n <= 0)
	{
		len++;
		if (n < 0)
			n = -n;
	}
	while (n > 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char			*str;
	size_t			len;
	long			nb;

	nb = (long)n;
	len = ft_intlen(nb);
	str = (char *)malloc(sizeof(char) * (len +1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (nb < 0)
	{
		str[0] = '-';
		nb = -nb;
	}
	if (nb == 0)
		str[0] = '0';
	while (nb > 0)
	{
		str[--len] = (nb % 10) + '0';
		nb /= 10;
	}
	return (str);
}

/*int	main(void)
{
	int	nb1 = 0;
	int	nb2 = -2147483648;
	int	nb3 = 2147483647;

	printf("nb1: %d; length: %zu\n", nb1, ft_intlen(nb1));
	printf("nb2: %d; length: %zu\n", nb2, ft_intlen(nb2));
	printf("nb3: %d; length: %zu\n", nb3, ft_intlen(nb3));

	printf("string: %s\n",ft_itoa(nb1));
	printf("string: %s\n",ft_itoa(nb2));
	printf("string: %s\n",ft_itoa(nb3));
}*/
