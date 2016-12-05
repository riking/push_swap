/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/27 21:38:43 by kyork             #+#    #+#             */
/*   Updated: 2016/12/05 13:53:58 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ps_stack.h"
#include "path.h"
#include "help_best.h"
#include <ft_printf.h>
#include <stdlib.h>

static int	cmp_int(void *left, void *right, size_t size, void *data)
{
	int		*a;
	int		*b;

	if (size != sizeof(int))
		exit(3);
	a = left;
	b = right;
	(void)data;
	if (*a < *b)
		return (1);
	if (*a > *b)
		return (-1);
	return (0);
}

int			main(int argc, char **argv)
{
	t_stack 	*st;
	t_stack 	*sorted;
	t_array		ops;
	size_t		idx;

	st = read_input(argc, argv);
	if (!st)
	{
		ft_dprintf(2, "Error\n");
		return (2);
	}
	print_stack(st);
	sorted = stack_clone(st);
	ft_ary_sort(&sorted->st_a, &cmp_int, NULL);
	//ops = p_do_solve(st, sorted);
	ops = help_sort(st, sorted);
	ops = p_optimize(ops, st, sorted);
	idx = 0;
	while (idx < ops.item_count)
		ft_printf("%s\n", op_name(*(t_op*)ft_ary_get(&ops, idx++)));
	stack_free(st);
	stack_free(sorted);
	ft_ary_destroy(&ops);
}
