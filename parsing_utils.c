/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valmoral <valmoral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 19:05:11 by valmoral          #+#    #+#             */
/*   Updated: 2026/04/17 19:05:22 by valmoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	match_flag(const char *arg, const char *flag)
{
	return (ft_strlen(arg) == ft_strlen(flag)
		&& ft_strncmp(arg, flag, ft_strlen(flag)) == 0);
}

static int	parse_digits(char *str, int i, unsigned long long limit,
	unsigned long long *value)
{
	unsigned long long	digit;

	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		digit = (unsigned long long)(str[i++] - '0');
		if (*value > (limit - digit) / 10ULL)
			return (0);
		*value = *value * 10ULL + digit;
	}
	return (1);
}

int	parse_long_long(char *str, long long *num)
{
	unsigned long long	value;
	unsigned long long	limit;
	int					sign;
	int					i;

	i = 0;
	sign = 1;
	value = 0;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign = -1;
	if (!str[i])
		return (0);
	limit = (unsigned long long)LLONG_MAX + (sign < 0);
	if (!parse_digits(str, i, limit, &value))
		return (0);
	if (sign < 0 && value == (unsigned long long)LLONG_MAX + 1ULL)
		*num = LLONG_MIN;
	else if (sign < 0)
		*num = -(long long)value;
	else
		*num = (long long)value;
	return (1);
}

int	parse_option(char *arg, t_parse_opts *opts)
{
	if (match_flag(arg, "--simple"))
		opts->strategy = SIMPLE;
	else if (match_flag(arg, "--insertion"))
		opts->strategy = INSERTION;
	else if (match_flag(arg, "--medium"))
		opts->strategy = MEDIUM;
	else if (match_flag(arg, "--complex"))
		opts->strategy = COMPLEX;
	else if (match_flag(arg, "--adaptive"))
		opts->strategy = ADAPTIVE;
	else if (match_flag(arg, "--bench"))
		opts->bench = 1;
	else
		return (0);
	return (1);
}

void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}
