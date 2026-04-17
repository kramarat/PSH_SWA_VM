/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kramarat <kramarat@student.42urduliz.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 18:06:06 by kramarat          #+#    #+#             */
/*   Updated: 2026/04/17 18:06:37 by kramarat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Accept optional sign followed by digits only. */
static int	is_valid_int(char *str)
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

/* Parse one token, validate range, reject duplicates, append to stack A. */
static int	parse_value(char *value, t_stack_node **a)
{
	long long		num;
	t_stack_node	*current;

	if (!is_valid_int(value))
		return (0);
	if (!parse_long_long(value, &num))
		return (0);
	if (num > INT_MAX || num < INT_MIN)
		return (0);
	current = *a;
	while (current)
	{
		if (current->number == (int)num)
			return (0);
		current = current->next;
	}
	add_node(a, (int)num);
	return (1);
}

/* Parse one argv item that may contain multiple space-separated values. */
static int	parse_values(char *arg, t_stack_node **a)
{
	char	**values;
	int		j;

	values = ft_split(arg, ' ');
	if (!values || !values[0])
		return (free_split(values), 0);
	j = 0;
	while (values[j] && parse_value(values[j], a))
		j++;
	if (values[j])
		return (free_split(values), 0);
	free_split(values);
	return (1);
}

/* Parse CLI flags and numbers into options + stack A. */
int	parse_args(int argc, char **argv, t_stack_node **a, t_parse_opts *opts)
{
	int	i;

	opts->strategy = ADAPTIVE;
	opts->bench = 0;
	i = 1;
	while (i < argc)
	{
		if (!parse_option(argv[i], opts) && !parse_values(argv[i], a))
			return (0);
		i++;
	}
	return (1);
}
