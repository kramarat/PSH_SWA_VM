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

char	**ft_split(char const *s, char c);

/* Checks if string is a valid integer */
int	is_valid_int(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

/* Checks for duplicates in stack */
int	has_duplicates(t_stack_node *stack, int num)
{
	while (stack)
	{
		if (stack->number == num)
			return (1);
		stack = stack->next;
	}
	return (0);
}

static void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

static int	parse_value(char *value, t_stack_node **a)
{
	long long	num;

	if (!is_valid_int(value))
		return (0);
	num = atoll(value);
	if (num > INT_MAX || num < INT_MIN)
		return (0);
	if (has_duplicates(*a, (int)num))
		return (0);
	add_node(a, (int)num);
	return (1);
}

static int	parse_values(char *arg, t_stack_node **a)
{
	char	**values;
	int		j;

	values = ft_split(arg, ' ');
	if (!values || !values[0])
	{
		free_split(values);
		return (0);
	}
	j = 0;
	while (values[j])
	{
		if (!parse_value(values[j], a))
		{
			free_split(values);
			return (0);
		}
		j++;
	}
	free_split(values);
	return (1);
}

/* Parses arguments, skipping selectors, builds stack a */
int	parse_args(int argc, char **argv, t_stack_node **a, t_strategy *strategy, int *bench)
{
	int				i;

	*strategy = ADAPTIVE;
	*bench = 0;
	i = 1;
	while (i < argc)
	{
		if (strcmp(argv[i], "--simple") == 0)
			*strategy = SIMPLE;
		else if (strcmp(argv[i], "--insertion") == 0)
			*strategy = INSERTION;
		else if (strcmp(argv[i], "--medium") == 0)
			*strategy = MEDIUM;
		else if (strcmp(argv[i], "--complex") == 0)
			*strategy = COMPLEX;
		else if (strcmp(argv[i], "--adaptive") == 0)
			*strategy = ADAPTIVE;
		else if (strcmp(argv[i], "--bench") == 0)
			*bench = 1;
		else if (!parse_values(argv[i], a))
			return (0);
		i++;
	}
	return (1);
}

/* Outputs benchmark info to stderr */
void	output_bench(double disorder, t_strategy strategy, t_strategy actual, t_op_counts counts)
{
	char	strategy_name[40];
	char	actual_name[24];
	int		total_ops;

	if (actual == SIMPLE)
		strcpy(actual_name, "Simple O(n^2)");
	else if (actual == INSERTION)
		strcpy(actual_name, "Insertion O(n^2)");
	else if (actual == MEDIUM)
		strcpy(actual_name, "Medium O(n √n)");
	else
		strcpy(actual_name, "Complex O(n log n)");
	if (strategy == SIMPLE)
		strcpy(strategy_name, "Simple O(n^2)");
	else if (strategy == INSERTION)
		strcpy(strategy_name, "Insertion O(n^2)");
	else if (strategy == MEDIUM)
		strcpy(strategy_name, "Medium O(n √n)");
	else if (strategy == COMPLEX)
		strcpy(strategy_name, "Complex O(n log n)");
	else
		snprintf(strategy_name, sizeof(strategy_name), "Adaptive -> %s", actual_name);
	total_ops = counts.sa + counts.sb + counts.ss + counts.pa + counts.pb +
				counts.ra + counts.rb + counts.rr + counts.rra + counts.rrb + counts.rrr;
	dprintf(2, "%.2f\n%s\n%d\nsa:%d sb:%d ss:%d pa:%d pb:%d ra:%d rb:%d rr:%d rra:%d rrb:%d rrr:%d\n",
			disorder, strategy_name, total_ops,
			counts.sa, counts.sb, counts.ss, counts.pa, counts.pb,
			counts.ra, counts.rb, counts.rr, counts.rra, counts.rrb, counts.rrr);
}

int	main(int argc, char **argv)
{
	t_stack_node	*a;
	t_stack_node	*b;
	t_strategy		strategy;
	t_strategy		actual_strategy;
	int				bench;
	t_op_counts		counts;
	double			disorder;

	a = NULL;
	b = NULL;
	memset(&counts, 0, sizeof(t_op_counts));
	if (argc == 1)
		return (0);
	if (!parse_args(argc, argv, &a, &strategy, &bench))
	{
		write(2, "Error\n", 6);
		free_stack(&a);
		return (1);
	}
	if (!a)
	{
		free_stack(&a);
		return (0);
	}
	disorder = compute_disorder(a);
	actual_strategy = strategy;
	if (strategy == ADAPTIVE)
		actual_strategy = select_adaptive_strategy(a, disorder);
	if (actual_strategy == SIMPLE)
		sort_simple(&a, &b, &counts);
	else if (actual_strategy == INSERTION)
		sort_insertion(&a, &b, &counts);
	else if (actual_strategy == MEDIUM)
		sort_medium(&a, &b, &counts);
	else if (actual_strategy == COMPLEX)
		sort_complex(&a, &b, &counts);
	else
		sort_adaptive(&a, &b, &counts);
	if (bench)
		output_bench(disorder, strategy, actual_strategy, counts);
	free_stack(&a);
	free_stack(&b);
	return (0);
}

