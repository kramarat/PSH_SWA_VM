/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_complex.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kramarat <kramarat@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 16:05:18 by kramarat          #+#    #+#             */
/*   Updated: 2026/03/31 16:29:47 by kramarat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* One radix bit pass: keep 1-bits in A, push 0-bits to B. */
static void	radix_pass(t_stack_node **a, t_stack_node **b,
	int bit, t_op_counts *counts)
{
	int	i;
	int	size;

	size = stack_size(*a);
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
}

/* Radix sort on normalized indexes for larger inputs. */
void	sort_complex(t_stack_node **a, t_stack_node **b, t_op_counts *counts)
{
	int	size;
	int	max_bits;
	int	bit;

	size = stack_size(*a);
	if (size <= 3 || is_sorted_stack(*a))
	{
		sort_small_stack(a, counts);
		return ;
	}
	if (!set_indexes(*a))
		return ;
	max_bits = 0;
	while ((size - 1) >> max_bits)
		max_bits++;
	bit = 0;
	while (bit < max_bits)
		radix_pass(a, b, bit++, counts);
}
