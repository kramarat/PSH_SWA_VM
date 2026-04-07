/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_insertion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kramarat <kramarat@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 00:00:00 by kramarat          #+#    #+#             */
/*   Updated: 2026/03/31 00:00:00 by kramarat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Keep only three values in A; move the rest to B. */
static void	push_but_keep_three(t_stack_node **a, t_stack_node **b,
	t_op_counts *counts)
{
	while (stack_size(*a) > 3)
		pb(a, b, counts);
}

/* Build sorted A by reinserting values from B one by one. */
void	sort_insertion(t_stack_node **a, t_stack_node **b, t_op_counts *counts)
{
	int	size;
	int	insert_pos;

	size = stack_size(*a);
	if (size <= 3 || is_sorted_stack(*a))
	{
		sort_small_stack(a, counts);
		return ;
	}
	push_but_keep_three(a, b, counts);
	sort_three(a, counts);
	while (*b)
	{
		insert_pos = find_insert_pos(*a, (*b)->number);
		rotate_a_to_top(a, insert_pos, counts);
		pa(a, b, counts);
	}
	rotate_a_to_top(a, find_min_pos(*a), counts);
}
