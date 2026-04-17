/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bench.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valmoral <valmoral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 19:04:11 by valmoral          #+#    #+#             */
/*   Updated: 2026/04/17 19:04:22 by valmoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	print_op_counts(t_op_counts counts, int fd);

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

static void	put_double_2_fd(double value, int fd)
{
	int	whole;
	int	frac;

	if (value < 0)
	{
		write(fd, "-", 1);
		value = -value;
	}
	whole = (int)value;
	frac = (int)((value - (double)whole) * 100.0 + 0.5);
	if (frac == 100)
	{
		whole++;
		frac = 0;
	}
	ft_putnbr_fd(whole, fd);
	write(fd, ".", 1);
	if (frac < 10)
		write(fd, "0", 1);
	ft_putnbr_fd(frac, fd);
}

/* Print disorder, strategy, total ops, and per-op breakdown to stderr. */
void	output_bench(double disorder, t_strategy strategy,
	t_strategy actual, t_op_counts counts)
{
	ft_putstr_fd("Disorder: ", 2);
	put_double_2_fd(disorder, 2);
	write(2, "\n", 1);
	ft_putstr_fd("Strategy: ", 2);
	if (strategy == ADAPTIVE)
	{
		ft_putstr_fd("Adaptive -> ", 2);
		ft_putstr_fd((char *)strategy_label(actual), 2);
	}
	else
		ft_putstr_fd((char *)strategy_label(strategy), 2);
	write(2, "\n", 1);
	ft_putstr_fd("Total ops: ", 2);
	ft_putnbr_fd(total_ops(counts), 2);
	write(2, "\n", 1);
	print_op_counts(counts, 2);
}
