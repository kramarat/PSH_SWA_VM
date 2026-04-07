/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kramarat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 18:06:41 by kramarat          #+#    #+#             */
/*   Updated: 2026/01/24 18:06:47 by kramarat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	node_count;

	node_count = 0;
	if (!lst)
		return (0);
	while (lst != NULL)
	{
		lst = lst->next;
		node_count++;
	}
	return (node_count);
}
