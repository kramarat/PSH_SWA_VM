/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_medium.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kramarat <kramarat@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 00:00:00 by kramarat          #+#    #+#             */
/*   Updated: 2026/03/31 00:00:00 by kramarat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Small helper for chunk size: ceil(sqrt(n)). */
static int	int_sqrt_ceil(int value)
{
	int	root;

	root = 1;
	while (root * root < value)
		root++;
	return (root);
}

/* Push A to B in chunks to reduce random movement. */
static void	push_chunks_to_b(t_stack_node **a, t_stack_node **b,
	int chunk_size, t_op_counts *counts)
{
	int	pushed;

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
}

/* Rebuild A by repeatedly taking max from B. */
static void	push_back_max_to_a(t_stack_node **a, t_stack_node **b,
	t_op_counts *counts)
{
	int	max_pos;

	while (*b)
	{
		max_pos = find_max_pos(*b);
		rotate_b_to_top(b, max_pos, counts);
		pa(a, b, counts);
	}
}

/* Chunk-based strategy for medium input sizes. */
void	sort_medium(t_stack_node **a, t_stack_node **b, t_op_counts *counts)
{
	int	size;
	int	chunk_size;

	size = stack_size(*a);
	if (size <= 3 || is_sorted_stack(*a))
	{
		sort_small_stack(a, counts);
		return ;
	}
	if (!set_indexes(*a))
		return ;
	chunk_size = int_sqrt_ceil(size);
	push_chunks_to_b(a, b, chunk_size, counts);
	push_back_max_to_a(a, b, counts);
}
