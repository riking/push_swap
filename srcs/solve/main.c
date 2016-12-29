/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/27 21:38:43 by kyork             #+#    #+#             */
/*   Updated: 2016/12/29 15:06:27 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ps_stack.h"
#include "path.h"
#include "merge.h"
#include <ft_printf.h>
#include <stdlib.h>

#define STRATEGY_P p_do_solve
#define STRATEGY_H help_sort
#define STRATEGY_M picked_sort

#define STRATEGY STRATEGY_M

static t_array	solve_it(t_stack *orig)
{
	t_array		ops;
	t_stack		*sorted;
	t_stack		*st2;

	sorted = stack_clone(orig);
	ft_ary_sort(&sorted->st_a, &cmp_int, NULL);
	st2 = stack_clone(orig);
	ops = STRATEGY(st2, sorted);
	stack_free(st2);
	ft_dprintf(2, "before optimization: count=%ld\n", ops.item_count);
	st2 = stack_clone(orig);
	ops = p_optimize(ops, st2, sorted, 2);
	stack_free(st2);
	stack_free(sorted);
	return (ops);
}

int				main(int argc, char **argv)
{
	t_stack		*st;
	t_array		ops;
	size_t		idx;

	st = read_input(argc, argv);
	if (!st)
	{
		ft_dprintf(2, "Error\n");
		return (2);
	}
	print_stack(st);
	ops = solve_it(st);
	idx = 0;
	while (idx < ops.item_count)
		ft_printf("%s\n", op_name(*(t_op*)ft_ary_get(&ops, idx++)));
	stack_free(st);
	ft_ary_destroy(&ops);
}
