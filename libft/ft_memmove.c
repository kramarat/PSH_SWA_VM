/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kramarat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 13:19:44 by kramarat          #+#    #+#             */
/*   Updated: 2026/01/24 13:20:48 by kramarat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*ptr_dest;

	ptr_dest = dest;
	if (ptr_dest < (unsigned char *) src)
		return (ft_memcpy(dest, src, n));
	else if (ptr_dest > (unsigned char *) src)
	{
		while (n--)
			ptr_dest[n] = ((unsigned char *) src)[n];
	}
	return (dest);
}
