/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valmoral <valmoral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 17:14:55 by valmoral          #+#    #+#             */
/*   Updated: 2026/03/12 17:14:56 by valmoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Parse args and build stack A.
   Returns -1 on error, 0 on empty input, 1 on success. */
static int	load_input(int argc, char **argv, t_stack_node **a,
	t_parse_opts *opts)
{
	if (!parse_args(argc, argv, a, opts))
	{
		write(2, "Error\n", 6);
		free_stack(a);
		return (-1);
	}
	if (!*a)
		return (0);
	return (1);
}

/* Pick the active strategy, run it, and optionally print benchmark data. */
static void	execute_sort(t_stack_node **a, t_stack_node **b,
	t_parse_opts opts, t_op_counts *counts)
{
	t_strategy	actual;
	double		disorder;

	disorder = compute_disorder(*a);
	actual = opts.strategy;
	if (opts.strategy == ADAPTIVE)
		actual = select_adaptive_strategy(*a, disorder);
	if (actual == SIMPLE)
		sort_simple(a, b, counts);
	else if (actual == INSERTION)
		sort_insertion(a, b, counts);
	else if (actual == MEDIUM)
		sort_medium(a, b, counts);
	else if (actual == COMPLEX)
		sort_complex(a, b, counts);
	else
		sort_adaptive(a, b, counts);
	if (opts.bench)
		output_bench(disorder, opts.strategy, actual, *counts);
}

/* Program entry point: parse, sort, report (optional), free everything. */
int	main(int argc, char **argv)
{
	t_stack_node	*a;
	t_stack_node	*b;
	t_parse_opts	opts;
	t_op_counts		counts;

	a = NULL;
	b = NULL;
	memset(&counts, 0, sizeof(t_op_counts));
	if (argc == 1)
		return (0);
	if (load_input(argc, argv, &a, &opts) < 0)
	{
		free_stack(&a);
		return (1);
	}
	if (!a)
	{
		free_stack(&a);
		return (0);
	}
	execute_sort(&a, &b, opts, &counts);
	free_stack(&a);
	free_stack(&b);
	return (0);
}
