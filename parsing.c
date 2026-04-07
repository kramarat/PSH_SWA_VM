/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valmoral <valmoral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 00:00:00 by valmoral          #+#    #+#             */
/*   Updated: 2026/03/31 00:00:00 by valmoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

char	**ft_split(char const *s, char c);

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

/* Free a NULL-terminated string array returned by ft_split. */
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

/* Parse one token, validate range, reject duplicates, append to stack A. */
static int	parse_value(char *value, t_stack_node **a)
{
	long long		num;
	t_stack_node	*current;

	if (!is_valid_int(value))
		return (0);
	num = atoll(value);
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

/* Parse CLI flags and numbers into options + stack A. */
int	parse_args(int argc, char **argv, t_stack_node **a, t_parse_opts *opts)
{
	int	i;

	i = 1;
	opts->strategy = ADAPTIVE;
	opts->bench = 0;
	while (i < argc)
	{
		if (strcmp(argv[i], "--simple") == 0)
			opts->strategy = SIMPLE;
		else if (strcmp(argv[i], "--insertion") == 0)
			opts->strategy = INSERTION;
		else if (strcmp(argv[i], "--medium") == 0)
			opts->strategy = MEDIUM;
		else if (strcmp(argv[i], "--complex") == 0)
			opts->strategy = COMPLEX;
		else if (strcmp(argv[i], "--adaptive") == 0)
			opts->strategy = ADAPTIVE;
		else if (strcmp(argv[i], "--bench") == 0)
			opts->bench = 1;
		else if (!parse_values(argv[i], a))
			return (0);
		i++;
	}
	return (1);
}
