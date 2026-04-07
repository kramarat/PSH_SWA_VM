/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_rotate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valmoral <valmoral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 17:14:50 by valmoral          #+#    #+#             */
/*   Updated: 2026/03/12 17:39:11 by valmoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Move top node to bottom of the same stack. */
void	rotate(t_stack_node **stack)
{
	t_stack_node	*last_node;
	int				size;

	size = stack_size(*stack);
	if (!stack || !*stack || size == 1)
		return ;
	last_node = find_last_node(*stack);
	last_node->next = *stack;
	*stack = (*stack)->next;
	(*stack)->previous = NULL;
	last_node->next->previous = last_node;
	last_node->next->next = NULL;
}

/* Rotate A + emit operation. */
void	ra(t_stack_node **a, t_op_counts *counts)
{
	rotate(a);
	counts->ra++;
	write(1, "ra\n", 3);
}

/* Rotate B + emit operation. */
void	rb(t_stack_node **b, t_op_counts *counts)
{
	rotate(b);
	counts->rb++;
	write(1, "rb\n", 3);
}

/* Rotate both stacks + emit operation. */
void	rr(t_stack_node **a, t_stack_node **b, t_op_counts *counts)
{
	rotate(a);
	rotate(b);
	counts->rr++;
	write(1, "rr\n", 3);
}
