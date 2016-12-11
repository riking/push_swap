/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/27 21:38:43 by kyork             #+#    #+#             */
/*   Updated: 2016/12/10 17:18:50 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ps_stack.h"
#include "path.h"
#include "help_best.h"
#include "roll.h"
#include <ft_printf.h>
#include <stdlib.h>

int			main(int argc, char **argv)
{
	t_stack 	*st;
	t_stack 	*sorted;
	t_stack		*st2;
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

	st2 = stack_clone(st);
	ops = p_do_solve(st, sorted);
	//ops = help_sort(st2, sorted);
	//ops = roll_solve(st2, sorted);
	stack_free(st2);

	ft_dprintf(2, "before optimization:\n");
	idx = 0;
	while (idx < ops.item_count)
		ft_dprintf(2, "%s ", op_name(*(t_op*)ft_ary_get(&ops, idx++)));
	ft_dprintf(2, "\n");
	st2 = stack_clone(st);
	ops = p_optimize(ops, st2, sorted);
	stack_free(st2);

	idx = 0;
	while (idx < ops.item_count)
		ft_printf("%s\n", op_name(*(t_op*)ft_ary_get(&ops, idx++)));
	stack_free(st);
	stack_free(sorted);
	ft_ary_destroy(&ops);
}
