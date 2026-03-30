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

/* Returns the number of nodes in the stack */
int	stack_size(t_stack_node *stack)
{
	int	size; // Counter for the size

	size = 0; // Initialize size to 0
	while (stack) // Loop through each node in the stack
	{
		size++; // Increment size for each node
		stack = stack->next; // Move to the next node
	}
	return (size); // Return the total size
}

/* Finds and returns the last node in the stack */
t_stack_node	*find_last_node(t_stack_node *stack)
{
	if (!stack) // If stack is empty, return NULL
		return (NULL);
	while (stack->next) // Traverse to the end of the stack
		stack = stack->next; // Move to the next node
	return (stack); // Return the last node
}

/* Adds a new node with the given number to the end of the stack */
void	add_node(t_stack_node **stack, int number)
{
	t_stack_node	*new_node; // Pointer to the new node
	t_stack_node	*last; // Pointer to the last node

	new_node = malloc(sizeof(t_stack_node)); // Allocate memory for new node
	if (!new_node) // If malloc fails, do nothing (error handling elsewhere)
		return ;
	new_node->number = number; // Set the number
	new_node->next = NULL; // New node is the last, so next is NULL
	new_node->previous = NULL; // Will be set below
	if (!*stack) // If stack is empty, new node is the first
	{
		*stack = new_node; // Set stack to new node
		return ;
	}
	last = find_last_node(*stack); // Find the current last node
	last->next = new_node; // Link last to new node
	new_node->previous = last; // Link new node back to last
}

/* Frees all nodes in the stack */
void	free_stack(t_stack_node **stack)
{
	t_stack_node	*temp; // Temporary pointer to hold current node

	while (*stack) // While there are nodes in the stack
	{
		temp = *stack; // Save current node
		*stack = (*stack)->next; // Move to next node
		free(temp); // Free the saved node
	}
}