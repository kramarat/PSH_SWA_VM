/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kramarat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 18:08:35 by kramarat          #+#    #+#             */
/*   Updated: 2026/01/24 18:08:48 by kramarat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	int		size;
	t_list	*last;

	size = ft_lstsize(lst) - 1;
	if (!lst)
		return (NULL);
	while (size--)
		lst = lst->next;
	last = lst;
	return (last);
}
