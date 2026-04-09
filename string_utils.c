/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valmoral <valmoral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 00:00:00 by valmoral          #+#    #+#             */
/*   Updated: 2026/04/09 21:31:42 by valmoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

size_t	ps_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	src_len;
	size_t	copy_len;
	size_t	index;

	src_len = strlen(src);
	if (size == 0)
		return (src_len);
	copy_len = src_len;
	if (copy_len >= size)
		copy_len = size - 1;
	index = 0;
	while (index < copy_len)
	{
		dst[index] = src[index];
		index++;
	}
	dst[index] = '\0';
	return (src_len);
}
