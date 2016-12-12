/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/27 16:10:53 by kyork             #+#    #+#             */
/*   Updated: 2016/12/11 01:29:19 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ps_check.h"
#include <ft_printf.h>
#include <libft.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

static int	g_print;
static int	g_sleep;

static void	do_sleep(void)
{
	usleep(1000 * 35);
}

static int	check(t_stack *st)
{
	char	*line;
	int		status;
	t_op	op;

	if (g_print)
		print_stack(st);
	while ((status = get_next_line(0, &line)) == 1)
	{
		op = parse_op(line);
		if (g_print)
			ft_printf("Exec %s:\n", line);
		free(line);
		if (op == OP_INVALID)
			return (-1);
		stack_do(st, op);
		if (g_print)
			print_stack(st);
		if (g_print && g_sleep)
			do_sleep();
	}
	if (st->st_b.item_count > 0)
		return (1);
	if (st->st_a.item_count == 0)
		return (0);
	return (is_sorted(st) ? 0 : 1);
}

static int	presult(int result)
{
	if (result == -1)
	{
		ft_dprintf(2, "Error\n");
		return (2);
	}
	if (result == 1)
		ft_printf("KO\n");
	else
		ft_printf("OK\n");
	return (result);
}

static int	on_opt(char opt)
{
	if (opt == 'v')
		g_print = 1;
	else if (opt == 's')
		g_sleep = 1;
	else
		return (-1);
	return (0);
}

static int	parse_opts(char **argv)
{
	int		i;
	int		ac;
	int		opt_count;

	ac = 1;
	opt_count = 0;
	while (argv[ac])
		if (argv[ac][0] == '-')
		{
			if (argv[ac][1] == 0)
				break ;
			if (ft_atoi(argv[ac]) != 0)
				break ;
			opt_count++;
			i = 0;
			while (argv[ac][++i])
				if (-1 == on_opt(argv[ac][i]))
					return (-1);
			ac++;
		}
		else
			break ;
	return (opt_count);
}

int			main(int argc, char **argv)
{
	t_stack		*st;
	int			ret;

	ret = parse_opts(argv);
	if (ret == -1)
		ft_dprintf(2, "Error\n");
	if (ret == -1)
		return (3);
	argc -= ret;
	argv += ret;
	st = read_input(argc, argv);
	if (!st)
	{
		ft_dprintf(2, "Error\n");
		return (2);
	}
	ret = presult(check(st));
	ft_dprintf(2, "[!!] op_count = %ld\n", st->ops.item_count);
	stack_free(st);
	return (ret);
}
