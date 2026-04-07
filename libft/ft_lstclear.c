/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kramarat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 18:12:15 by kramarat          #+#    #+#             */
/*   Updated: 2026/01/24 18:12:29 by kramarat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;
	t_list	*node;

	if (!lst)
		return ;
	node = *lst;
	while (node != NULL)
	{
		tmp = node;
		(*del)(node->content);
		node = node->next;
		free(tmp);
	}
	*lst = NULL;
}
