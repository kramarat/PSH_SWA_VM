/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_simple.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valmoral <valmoral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 19:06:01 by valmoral          #+#    #+#             */
/*   Updated: 2026/04/17 19:06:07 by valmoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Encode the needed operation pattern for 3 numbers. */
static int	sort_three_case(int first, int second, int third)
{
	if (first > second && second < third && first < third)
		return (1);
	else if (first > second && second > third)
		return (2);
	else if (first > second && second < third && first > third)
		return (3);
	else if (first < second && second > third && first < third)
		return (4);
	else if (first < second && second > third && first > third)
		return (5);
	return (0);
}

/* Apply the encoded case returned by sort_three_case. */
static void	apply_sort_three_case(int c, t_stack_node **a, t_op_counts *counts)
{
	if (c == 1)
		sa(a, counts);
	else if (c == 2)
	{
		sa(a, counts);
		rra(a, counts);
	}
	else if (c == 3)
		ra(a, counts);
	else if (c == 4)
	{
		sa(a, counts);
		ra(a, counts);
	}
	else if (c == 5)
		rra(a, counts);
}

/* Minimal sort for exactly 3 elements. */
void	sort_three(t_stack_node **a, t_op_counts *counts)
{
	int	first;
	int	second;
	int	third;
	int	c;

	if (stack_size(*a) != 3)
		return ;
	first = (*a)->number;
	second = (*a)->next->number;
	third = (*a)->next->next->number;
	c = sort_three_case(first, second, third);
	apply_sort_three_case(c, a, counts);
}

/* Selection-style sort using stack B as temporary storage. */
void	sort_simple(t_stack_node **a, t_stack_node **b, t_op_counts *counts)
{
	int	size;
	int	min_pos;

	size = stack_size(*a);
	if (size <= 3 || is_sorted_stack(*a))
	{
		sort_small_stack(a, counts);
		return ;
	}
	while (stack_size(*a) > 3)
	{
		min_pos = find_min_pos(*a);
		rotate_a_to_top(a, min_pos, counts);
		pb(a, b, counts);
	}
	sort_three(a, counts);
	while (*b)
		pa(a, b, counts);
}
