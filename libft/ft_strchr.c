/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kramarat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 18:29:45 by kramarat          #+#    #+#             */
/*   Updated: 2026/01/27 18:30:31 by kramarat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*ptr;

	i = 0;
	ptr = (char *)s;
	while (ptr[i] && (ptr[i] != (unsigned char)c))
		i++;
	if (ptr[i] == (unsigned char)c)
		return (&ptr[i]);
	return (NULL);
}
/*
int	main(void)
{
	char	s[] = "lazy fox jumps over quick brown dog";
	char	c = 'o' + 256;

	printf("ft_strchr: %s\n", ft_strchr(s, c));
	printf("strchr: %s\n", strchr(s, c));
}*/
/*without typecasting c, failing following tests
(does not compile with -Werror flag):
check(ft_strchr(s, 't' + 256) == s); showLeaks();
res = single_test_strrchr(5, "teste", 1024 + 'e') && res;
res = single_test_strrchr(6, "teste", 1024) && res;
*/
