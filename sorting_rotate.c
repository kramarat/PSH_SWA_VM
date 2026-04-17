/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_rotate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kramarat <kramarat@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 20:05:57 by kramarat          #+#    #+#             */
/*   Updated: 2026/03/31 20:06:22 by kramarat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Return position of minimum value in the given stack. */
int	find_min_pos(t_stack_node *stack)
{
	int				min_pos;
	int				min_value;
	int				pos;
	t_stack_node	*current;

	if (!stack)
		return (-1);
	min_pos = 0;
	min_value = stack->number;
	pos = 0;
	current = stack;
	while (current)
	{
		if (current->number < min_value)
		{
			min_value = current->number;
			min_pos = pos;
		}
		pos++;
		current = current->next;
	}
	return (min_pos);
}

/* Return position of maximum value in the given stack. */
int	find_max_pos(t_stack_node *stack)
{
	int				max_pos;
	int				max_value;
	int				pos;
	t_stack_node	*current;

	if (!stack)
		return (-1);
	max_pos = 0;
	max_value = stack->number;
	pos = 0;
	current = stack;
	while (current)
	{
		if (current->number > max_value)
		{
			max_value = current->number;
			max_pos = pos;
		}
		pos++;
		current = current->next;
	}
	return (max_pos);
}

/* Bring chosen position to top of stack A with shortest path. */
void	rotate_a_to_top(t_stack_node **stack, int pos, t_op_counts *counts)
{
	int	size;
	int	i;

	size = stack_size(*stack);
	if (pos < 0 || pos >= size)
		return ;
	i = 0;
	if (pos <= size / 2)
		while (i++ < pos)
			ra(stack, counts);
	else
		while (i++ < size - pos)
			rra(stack, counts);
}

/* Bring chosen position to top of stack B with shortest path. */
void	rotate_b_to_top(t_stack_node **stack, int pos, t_op_counts *counts)
{
	int	size;
	int	i;

	size = stack_size(*stack);
	if (pos < 0 || pos >= size)
		return ;
	i = 0;
	if (pos <= size / 2)
		while (i++ < pos)
			rb(stack, counts);
	else
		while (i++ < size - pos)
			rrb(stack, counts);
}
