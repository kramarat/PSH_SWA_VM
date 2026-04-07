/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bench.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valmoral <valmoral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 00:00:00 by valmoral          #+#    #+#             */
/*   Updated: 2026/03/31 00:00:00 by valmoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Human-readable label for a strategy enum value. */
static const char	*strategy_label(t_strategy strategy)
{
	if (strategy == SIMPLE)
		return ("Simple O(n^2)");
	if (strategy == INSERTION)
		return ("Insertion O(n^2)");
	if (strategy == MEDIUM)
		return ("Medium O(n sqrt(n))");
	return ("Complex O(n log n)");
}

/* Sum all operations for quick benchmark overview. */
static int	total_ops(t_op_counts counts)
{
	return (counts.sa + counts.sb + counts.ss + counts.pa + counts.pb
		+ counts.ra + counts.rb + counts.rr + counts.rra
		+ counts.rrb + counts.rrr);
}

/* Print disorder, strategy, total ops, and per-op breakdown to stderr. */
void	output_bench(double disorder, t_strategy strategy,
	t_strategy actual, t_op_counts counts)
{
	char	actual_name[24];
	char	strategy_name[40];

	strlcpy(actual_name, strategy_label(actual), sizeof(actual_name));
	if (strategy == ADAPTIVE)
		snprintf(strategy_name, sizeof(strategy_name), "Adaptive -> %s",
			actual_name);
	else
		strlcpy(strategy_name, strategy_label(strategy), sizeof(strategy_name));
	dprintf(2, "%.2f\n%s\n%d\n", disorder, strategy_name, total_ops(counts));
	dprintf(2, "sa:%d sb:%d ss:%d pa:%d pb:%d ra:%d rb:%d rr:%d ",
		counts.sa, counts.sb, counts.ss, counts.pa,
		counts.pb, counts.ra, counts.rb, counts.rr);
	dprintf(2, "rra:%d rrb:%d rrr:%d\n", counts.rra, counts.rrb, counts.rrr);
}
