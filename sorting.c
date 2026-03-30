/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kramarat <kramarat@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 19:01:23 by kramarat          #+#    #+#             */
/*   Updated: 2026/03/30 19:04:42 by kramarat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	is_sorted(t_stack_node *stack)
{
	while (stack && stack->next)
	{
		if (stack->number > stack->next->number)
			return (0);
		stack = stack->next;
	}
	return (1);
}

static void	sort_small(t_stack_node **a, t_op_counts *counts)
{
	int	size;

	size = stack_size(*a);
	if (size < 2 || is_sorted(*a))
		return ;
	if (size == 2)
	{
		if ((*a)->number > (*a)->next->number)
			sa(a, counts);
		return ;
	}
	sort_three(a, counts);
}

/* Calculates the disorder index: fraction of inverted pairs */
double	compute_disorder(t_stack_node *a)
{
	int			mistakes;
	int			total_pairs;
	t_stack_node	*node_i;
	t_stack_node	*node_j;

	if (stack_size(a) < 2)
		return (0.0);
	mistakes = 0;
	total_pairs = 0;
	node_i = a;
	while (node_i && node_i->next)
	{
		node_j = node_i->next;
		while (node_j)
		{
			total_pairs++;
			if (node_i->number > node_j->number)
				mistakes++;
			node_j = node_j->next;
		}
		node_i = node_i->next;
	}
	return ((double)mistakes / total_pairs);
}

/* Sorts a stack of 3 elements using minimal operations */
void	sort_three(t_stack_node **a, t_op_counts *counts)
{
	int	first;
	int	second;
	int	third;

	if (stack_size(*a) != 3)
		return ;
	first = (*a)->number;
	second = (*a)->next->number;
	third = (*a)->next->next->number;
	if (first > second && second < third && first < third)
		sa(a, counts);
	else if (first > second && second > third)
	{
		sa(a, counts);
		rra(a, counts);
	}
	else if (first > second && second < third && first > third)
		ra(a, counts);
	else if (first < second && second > third && first < third)
	{
		sa(a, counts);
		ra(a, counts);
	}
	else if (first < second && second > third && first > third)
		rra(a, counts);
}

static int	find_min_pos(t_stack_node *stack)
{
	int			min_pos;
	int			min_value;
	int			pos;
	t_stack_node	*current;

	if (!stack)
		return (-1);
	min_pos = 0;
	min_value = stack->number;
	current = stack;
	pos = 0;
	while (current)
	{
		if (current->number < min_value)
		{
			min_value = current->number;
			min_pos = pos;
		}
		current = current->next;
		pos++;
	}
	return (min_pos);
}

static int	find_max_pos(t_stack_node *stack)
{
	int			max_pos;
	int			max_value;
	int			pos;
	t_stack_node	*current;

	if (!stack)
		return (-1);
	max_pos = 0;
	max_value = stack->number;
	current = stack;
	pos = 0;
	while (current)
	{
		if (current->number > max_value)
		{
			max_value = current->number;
			max_pos = pos;
		}
		current = current->next;
		pos++;
	}
	return (max_pos);
}

static void	rotate_a_to_top(t_stack_node **stack, int pos, t_op_counts *counts)
{
	int	size;
	int	i;

	size = stack_size(*stack);
	if (pos < 0 || pos >= size)
		return ;
	if (pos <= size / 2)
	{
		i = 0;
		while (i < pos)
		{
			ra(stack, counts);
			i++;
		}
	}
	else
	{
		i = 0;
		while (i < size - pos)
		{
			rra(stack, counts);
			i++;
		}
	}
}

static void	rotate_b_to_top(t_stack_node **stack, int pos, t_op_counts *counts)
{
	int	size;
	int	i;

	size = stack_size(*stack);
	if (pos < 0 || pos >= size)
		return ;
	if (pos <= size / 2)
	{
		i = 0;
		while (i < pos)
		{
			rb(stack, counts);
			i++;
		}
	}
	else
	{
		i = 0;
		while (i < size - pos)
		{
			rrb(stack, counts);
			i++;
		}
	}
}

static int	int_sqrt_ceil(int value)
{
	int	root;

	root = 1;
	while (root * root < value)
		root++;
	return (root);
}

/* Simple sort O(n^2) using selection sort */
void	sort_simple(t_stack_node **a, t_stack_node **b, t_op_counts *counts)
{
	int	size;
	int	i;
	int	min_pos;

	size = stack_size(*a);
	if (size <= 3 || is_sorted(*a))
	{
		sort_small(a, counts);
		return ;
	}
	i = 0;
	while (i < size)
	{
		min_pos = find_min_pos(*a);
		rotate_a_to_top(a, min_pos, counts);
		pb(a, b, counts);
		i++;
	}
	while (*b)
		pa(a, b, counts);
}

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

static int	set_indexes(t_stack_node *a)
{
	int			size;
	int			i;
	int			*values;
	t_stack_node	*current;

	size = stack_size(a);
	values = malloc(sizeof(int) * size);
	if (!values)
		return (0);
	i = 0;
	current = a;
	while (current)
	{
		values[i++] = current->number;
		current = current->next;
	}
	current = a;
	while (current)
	{
		current->index = count_lower(values, size, current->number);
		current = current->next;
	}
	free(values);
	return (1);
}

static int	find_insert_pos(t_stack_node *a, int value)
{
	int			pos;
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

void	sort_insertion(t_stack_node **a, t_stack_node **b, t_op_counts *counts)
{
	int	size;
	int	insert_pos;

	size = stack_size(*a);
	if (size <= 3 || is_sorted(*a))
	{
		sort_small(a, counts);
		return ;
	}
	while (stack_size(*a) > 3)
		pb(a, b, counts);
	sort_three(a, counts);
	while (*b)
	{
		insert_pos = find_insert_pos(*a, (*b)->number);
		rotate_a_to_top(a, insert_pos, counts);
		pa(a, b, counts);
	}
	rotate_a_to_top(a, find_min_pos(*a), counts);
}

/* Medium sort O(n √n) using chunked pushes */
void	sort_medium(t_stack_node **a, t_stack_node **b, t_op_counts *counts)
{
	int	size;
	int	chunk_size;
	int	pushed;
	int	max_pos;

	size = stack_size(*a);
	if (size <= 3 || is_sorted(*a))
	{
		sort_small(a, counts);
		return ;
	}
	if (!set_indexes(*a))
		return ;
	chunk_size = int_sqrt_ceil(size);
	pushed = 0;
	while (*a)
	{
		if ((*a)->index <= pushed)
		{
			pb(a, b, counts);
			if (*b && (*b)->next)
				rb(b, counts);
			pushed++;
		}
		else if ((*a)->index <= pushed + chunk_size)
		{
			pb(a, b, counts);
			pushed++;
		}
		else
			ra(a, counts);
	}
	while (*b)
	{
		max_pos = find_max_pos(*b);
		rotate_b_to_top(b, max_pos, counts);
		pa(a, b, counts);
	}
}

void	sort_complex(t_stack_node **a, t_stack_node **b, t_op_counts *counts)
{
	int	size;
	int	max_bits;
	int	bit;
	int	i;

	size = stack_size(*a);
	if (size <= 3 || is_sorted(*a))
	{
		sort_small(a, counts);
		return ;
	}
	if (!set_indexes(*a))
		return ;
	max_bits = 0;
	while ((size - 1) >> max_bits)
		max_bits++;
	bit = 0;
	while (bit < max_bits)
	{
		i = 0;
		while (i < size)
		{
			if (((*a)->index >> bit) & 1)
				ra(a, counts);
			else
				pb(a, b, counts);
			i++;
		}
		while (*b)
			pa(a, b, counts);
		bit++;
	}
}

/* Adaptive sort based on size and disorder */
t_strategy	select_adaptive_strategy(t_stack_node *a, double disorder)
{
	int	size;

	size = stack_size(a);
	if (size <= 5 || disorder < 0.12)
		return (SIMPLE);
	if (size <= 32 || disorder < 0.35)
		return (INSERTION);
	if (size <= 150 || disorder < 0.65)
		return (MEDIUM);
	return (COMPLEX);
}

/* Adaptive sort based on size and disorder */
void	sort_adaptive(t_stack_node **a, t_stack_node **b, t_op_counts *counts)
{
	double	disorder;
	t_strategy	strategy;

	disorder = compute_disorder(*a);
	strategy = select_adaptive_strategy(*a, disorder);
	if (strategy == SIMPLE)
		sort_simple(a, b, counts);
	else if (strategy == INSERTION)
		sort_insertion(a, b, counts);
	else if (strategy == MEDIUM)
		sort_medium(a, b, counts);
	else
		sort_complex(a, b, counts);
}