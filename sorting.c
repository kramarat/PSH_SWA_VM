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

/* Count inversions for one node against all nodes to its right. */
static int	count_inversions_from(t_stack_node *node_i)
{
	int				mistakes;
	t_stack_node	*node_j;

	mistakes = 0;
	node_j = node_i->next;
	while (node_j)
	{
		if (node_i->number > node_j->number)
			mistakes++;
		node_j = node_j->next;
	}
	return (mistakes);
}

/* Count remaining pair combinations for one left-side node. */
static int	count_pairs_from(t_stack_node *node_i)
{
	int				pairs;
	t_stack_node	*node_j;

	pairs = 0;
	node_j = node_i->next;
	while (node_j)
	{
		pairs++;
		node_j = node_j->next;
	}
	return (pairs);
}

/*
** WHY DISORDER?
** Instead of blindly picking a strategy by size alone we also measure
** how scrambled the stack is. Disorder = (inverted pairs) / (total pairs).
** 0.0 means already sorted. 1.0 means fully reversed.
** This lets a nearly-sorted large stack still use a cheap strategy.
*/
double	compute_disorder(t_stack_node *a)
{
	int				mistakes;
	int				total_pairs;
	t_stack_node	*node_i;

	if (stack_size(a) < 2)
		return (0.0);
	mistakes = 0;
	total_pairs = 0;
	node_i = a;
	while (node_i && node_i->next)
	{
		total_pairs += count_pairs_from(node_i);
		mistakes += count_inversions_from(node_i);
		node_i = node_i->next;
	}
	return ((double)mistakes / total_pairs);
}

/*
** WHY EACH THRESHOLD?
** SIMPLE  (<=5 or disorder<0.12): tiny or nearly-sorted stacks.
**   Selection sort by min-finding is cheapest when there's almost nothing
**   to move.
** INSERTION (<=32 or disorder<0.35): small-medium or mildly shuffled.
**   Targeting each element's exact insertion position beats chunk overhead.
** MEDIUM (<=150 or disorder<0.65): medium stacks.
**   Chunk-based O(n*sqrt(n)): split into sqrt(n) ranges, push all to B,
**   pull back largest-first. Good balance of move-count vs complexity.
** COMPLEX (everything else): large, chaotic stacks.
**   Radix sort on normalised indexes is O(n*log n) and scales best.
*/
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

/*
** WHY ADAPTIVE?
** No single strategy wins for every input. Adaptive measures disorder
** first (cheap O(n^2) pass) then delegates so the right algorithm runs.
** An already-sorted 500-element stack costs 0 ops instead of running
** radix unnecessarily.
*/
void	sort_adaptive(t_stack_node **a, t_stack_node **b, t_op_counts *counts)
{
	double			disorder;
	t_strategy		strategy;

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
