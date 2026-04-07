/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_swap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valmoral <valmoral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 17:14:52 by valmoral          #+#    #+#             */
/*   Updated: 2026/03/12 17:38:10 by valmoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Swap top two nodes of one stack. */
void	swap(t_stack_node **stack)
{
	t_stack_node	*first_node;
	t_stack_node	*second_node;

	if (!*stack || !stack || stack_size(*stack) == 1)
		return ;
	first_node = *stack;
	second_node = (*stack)->next;
	first_node->previous = second_node;
	first_node->next = second_node->next;
	second_node->previous = NULL;
	second_node->next = first_node;
	if (first_node->next)
		first_node->next->previous = first_node;
	*stack = second_node;
}

/* Swap A + emit operation. */
void	sa(t_stack_node **a, t_op_counts *counts)
{
	swap(a);
	counts->sa++;
	write(1, "sa\n", 3);
}

/* Swap B + emit operation. */
void	sb(t_stack_node **b, t_op_counts *counts)
{
	swap(b);
	counts->sb++;
	write(1, "sb\n", 3);
}

/* Swap both stacks + emit operation. */
void	ss(t_stack_node **a, t_stack_node **b, t_op_counts *counts)
{
	swap(a);
	swap(b);
	counts->ss++;
	write(1, "ss\n", 3);
}
