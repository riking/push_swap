/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/27 16:10:53 by kyork             #+#    #+#             */
/*   Updated: 2016/12/11 00:53:36 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ps_check.h"
#include <ft_printf.h>
#include <stdlib.h>

static int	check(bool print, t_stack *st)
{
	char	*line;
	int		status;
	t_op	op;

	if (print)
		print_stack(st);
	while ((status = get_next_line(0, &line)) == 1)
	{
		op = parse_op(line);
		if (print)
			ft_printf("Exec %s:\n", line);
		free(line);
		if (op == OP_INVALID)
			return (-1);
		stack_do(st, op);
		if (print)
			print_stack(st);
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

int			main(int argc, char **argv)
{
	t_stack		*st;
	bool		print;
	int			ret;

	print = (0 == ft_strcmp(argv[1], "-v"));
	if (print)
		argc--;
	if (print)
		argv++;
	st = read_input(argc, argv);
	if (!st)
	{
		ft_dprintf(2, "Error\n");
		return (2);
	}
	ret = presult(check(print, st));
	ft_dprintf(2, "[!!] op_count = %ld\n", st->ops.item_count);
	stack_free(st);
	return (ret);
}
