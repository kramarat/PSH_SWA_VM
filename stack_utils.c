/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kramarat <kramarat@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 19:00:21 by kramarat          #+#    #+#             */
/*   Updated: 2026/03/30 19:00:28 by kramarat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Count nodes in a stack. */
int	stack_size(t_stack_node *stack)
{
	int	size;

	size = 0;
	while (stack)
	{
		size++;
		stack = stack->next;
	}
	return (size);
}

/* Return last node in stack, or NULL if empty. */
t_stack_node	*find_last_node(t_stack_node *stack)
{
	if (!stack)
		return (NULL);
	while (stack->next)
		stack = stack->next;
	return (stack);
}

/* Append one new value at the end of stack. */
void	add_node(t_stack_node **stack, int number)
{
	t_stack_node	*new_node;
	t_stack_node	*last;

	new_node = malloc(sizeof(t_stack_node));
	if (!new_node)
		return ;
	new_node->number = number;
	new_node->next = NULL;
	new_node->previous = NULL;
	if (!*stack)
	{
		*stack = new_node;
		return ;
	}
	last = find_last_node(*stack);
	last->next = new_node;
	new_node->previous = last;
}

/* Free all nodes in stack and leave it empty. */
void	free_stack(t_stack_node **stack)
{
	t_stack_node	*temp;

	while (*stack)
	{
		temp = *stack;
		*stack = (*stack)->next;
		free(temp);
	}
}
