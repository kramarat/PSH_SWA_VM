/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_common.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valmoral <valmoral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 19:05:36 by valmoral          #+#    #+#             */
/*   Updated: 2026/04/17 19:05:45 by valmoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Return 1 if stack is already ascending, else 0. */
int	is_sorted_stack(t_stack_node *stack)
{
	while (stack && stack->next)
	{
		if (stack->number > stack->next->number)
			return (0);
		stack = stack->next;
	}
	return (1);
}

/* Handle tiny cases (2 or 3 values) with minimal moves. */
void	sort_small_stack(t_stack_node **a, t_op_counts *counts)
{
	int	size;

	size = stack_size(*a);
	if (size < 2 || is_sorted_stack(*a))
		return ;
	if (size == 2)
	{
		if ((*a)->number > (*a)->next->number)
			sa(a, counts);
		return ;
	}
	sort_three(a, counts);
}
