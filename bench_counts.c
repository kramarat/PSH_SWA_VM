/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bench_counts.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valmoral <valmoral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 19:04:40 by valmoral          #+#    #+#             */
/*   Updated: 2026/04/17 19:04:47 by valmoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	print_pair(char *label, int value, int fd)
{
	ft_putstr_fd(label, fd);
	ft_putnbr_fd(value, fd);
}

void	print_op_counts(t_op_counts counts, int fd)
{
	print_pair("sa=", counts.sa, fd);
	print_pair(" sb=", counts.sb, fd);
	print_pair(" ss=", counts.ss, fd);
	print_pair(" pa=", counts.pa, fd);
	print_pair(" pb=", counts.pb, fd);
	print_pair(" ra=", counts.ra, fd);
	print_pair(" rb=", counts.rb, fd);
	print_pair(" rr=", counts.rr, fd);
	print_pair(" rra=", counts.rra, fd);
	print_pair(" rrb=", counts.rrb, fd);
	print_pair(" rrr=", counts.rrr, fd);
	write(fd, "\n", 1);
}
