/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_reverse_rotate.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valmoral <valmoral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 17:14:48 by valmoral          #+#    #+#             */
/*   Updated: 2026/03/12 17:39:27 by valmoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*Last node is sent to the top of the stack*/
void	reverse_rotate(t_stack_node **stack)
{
	t_stack_node	*last_node;
	int				size;

	size = stack_size(*stack);
	if (!stack || !*stack || size == 1)
		return ;
	last_node = find_last_node(*stack);
	last_node->previous->next = NULL;
	last_node->next = *stack;
	(*stack)->previous = last_node;
	last_node->previous = NULL;
	*stack = last_node;
}

void	rra(t_stack_node **a, t_op_counts *counts)
{
	reverse_rotate(a);
	counts->rra++;
	write(1, "rra\n", 4);
}

void	rrb(t_stack_node **b, t_op_counts *counts)
{
	reverse_rotate(b);
	counts->rrb++;
	write(1, "rrb\n", 4);
}

void	rrr(t_stack_node **a, t_stack_node **b, t_op_counts *counts)
{
	reverse_rotate(a);
	reverse_rotate(b);
	counts->rrr++;
	write(1, "rrr\n", 4);
}