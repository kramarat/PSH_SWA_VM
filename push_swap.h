/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valmoral <valmoral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 17:15:01 by valmoral          #+#    #+#             */
/*   Updated: 2026/03/12 17:42:57 by valmoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*TEMPPPPP - modify asap*/
#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <unistd.h>
# include <stdbool.h>
# include <limits.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>

typedef struct s_op_counts
{
	int	sa;
	int	sb;
	int	ss;
	int	pa;
	int	pb;
	int	ra;
	int	rb;
	int	rr;
	int	rra;
	int	rrb;
	int	rrr;
} 	t_op_counts;

typedef enum e_strategy
{
	SIMPLE,
	INSERTION,
	MEDIUM,
	COMPLEX,
	ADAPTIVE
} 	t_strategy;

/*	T_STACK_NODE STRUCTURE 

This is the data structure that will form the stack to be sorted.
Contains all necessary metadata to evaluate the optimal move and sort
the initial stack following the "game rules".

*previous		Link to previous node in stack.
number 			Number to be sorted.
curr_index		Current position in the stack.
cost_to_push	Cost to push this particular node from stack b to stack a.
is_cheapest		Flags cheapest node to push.
above_median 	Flags whether this node is nearer to top or bottom of stack.
*target_node	The node on top of which this node must be pushed.
*next			Link to next node in stack.									*/

typedef struct s_list
{
	struct s_list	*previous;
	int				number;
	int				index;
	int				cost_to_push;
	bool			is_cheapest;
	bool			above_middle;
	struct s_list	*target_node;
	struct s_list	*next;
}	t_stack_node;

//	aux_swap.C
void			swap(t_stack_node **stack);
void			sa(t_stack_node **a, t_op_counts *counts);
void			sb(t_stack_node **b, t_op_counts *counts);
void			ss(t_stack_node **a, t_stack_node **b, t_op_counts *counts);

//	aux_push.C
void			push(t_stack_node **dest, t_stack_node **src);
void			pa(t_stack_node **a, t_stack_node **b, t_op_counts *counts);
void			pb(t_stack_node **b, t_stack_node **a, t_op_counts *counts);

//	aux_rotate.C
void			rotate(t_stack_node **stack);
void			ra(t_stack_node **a, t_op_counts *counts);
void			rb(t_stack_node **b, t_op_counts *counts);
void			rr(t_stack_node **a, t_stack_node **b, t_op_counts *counts);

//	aux_reverse_rotate.C
void			reverse_rotate(t_stack_node **stack);
void			rra(t_stack_node **a, t_op_counts *counts);
void			rrb(t_stack_node **b, t_op_counts *counts);
void			rrr(t_stack_node **a, t_stack_node **b, t_op_counts *counts);

//	stack_utils.c
int				stack_size(t_stack_node *stack);
t_stack_node	*find_last_node(t_stack_node *stack);
void			add_node(t_stack_node **stack, int number);
void			free_stack(t_stack_node **stack);

//	sorting.c
double			compute_disorder(t_stack_node *a);
t_strategy		select_adaptive_strategy(t_stack_node *a, double disorder);
void			sort_three(t_stack_node **a, t_op_counts *counts);
void			sort_simple(t_stack_node **a, t_stack_node **b, t_op_counts *counts);
void			sort_insertion(t_stack_node **a, t_stack_node **b, t_op_counts *counts);
void			sort_medium(t_stack_node **a, t_stack_node **b, t_op_counts *counts);
void			sort_complex(t_stack_node **a, t_stack_node **b, t_op_counts *counts);
void			sort_adaptive(t_stack_node **a, t_stack_node **b, t_op_counts *counts);

#endif