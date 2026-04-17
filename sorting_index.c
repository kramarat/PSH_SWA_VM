/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_index.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kramarat <kramarat@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 17:48:53 by kramarat          #+#    #+#             */
/*   Updated: 2026/03/31 18:03:11 by kramarat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Count how many values are lower than the given value. */
static int	count_lower(int *arr, int size, int value)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i < size)
	{
		if (arr[i] < value)
			count++;
		i++;
	}
	return (count);
}

static void	fill_values(t_stack_node *stack, int *values)
{
	while (stack)
	{
		*values++ = stack->number;
		stack = stack->next;
	}
}

/* Assign normalized index (rank) to each node value. */
int	set_indexes(t_stack_node *a)
{
	int				size;
	int				*values;
	t_stack_node	*current;

	size = stack_size(a);
	values = malloc(sizeof(int) * size);
	if (!values)
		return (0);
	fill_values(a, values);
	current = a;
	while (current)
	{
		current->index = count_lower(values, size, current->number);
		current = current->next;
	}
	free(values);
	return (1);
}

/* Find insertion spot in circularly sorted stack A for value. */
int	find_insert_pos(t_stack_node *a, int value)
{
	int				pos;
	t_stack_node	*current;
	t_stack_node	*previous;

	pos = 0;
	previous = find_last_node(a);
	current = a;
	while (current)
	{
		if (previous->number < current->number)
		{
			if (value > previous->number && value < current->number)
				return (pos);
		}
		else if (value > previous->number || value < current->number)
			return (pos);
		previous = current;
		current = current->next;
		pos++;
	}
	return (0);
}
