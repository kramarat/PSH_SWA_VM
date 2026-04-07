/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_push.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valmoral <valmoral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 17:14:46 by valmoral          #+#    #+#             */
/*   Updated: 2026/03/12 17:38:26 by valmoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Move top node from src to dest. */
void	push(t_stack_node **dest, t_stack_node **src)
{
	t_stack_node	*node_to_push;

	if (!*src)
		return ;
	node_to_push = *src;
	*src = (*src)->next;
	if (*src)
		(*src)->previous = NULL;
	node_to_push->previous = NULL;
	if (!*dest)
	{
		*dest = node_to_push;
		node_to_push->next = NULL;
	}
	else
	{
		node_to_push->next = *dest;
		node_to_push->next->previous = node_to_push;
		*dest = node_to_push;
	}
}

/* Push from B to A + emit operation. */
void	pa(t_stack_node **a, t_stack_node **b, t_op_counts *counts)
{
	push(a, b);
	counts->pa++;
	write(1, "pa\n", 3);
}

/* Push from A to B + emit operation. */
void	pb(t_stack_node **a, t_stack_node **b, t_op_counts *counts)
{
	push(b, a);
	counts->pb++;
	write(1, "pb\n", 3);
}
