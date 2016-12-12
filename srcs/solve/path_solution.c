/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_solve.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/27 22:11:22 by kyork             #+#    #+#             */
/*   Updated: 2016/12/12 15:29:25 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "path.h"
#include <ft_printf.h>

static void	collect(t_array *ops, t_pnode *n)
{
	t_op	op;

	while (n->prev)
	{
		op = n->prev_op;
		if (n->from_solved)
			op = op_inverse(op);
		if (n->from_solved)
			ft_ary_append(ops, &op);
		else
			ft_ary_insert(ops, &op, 0);
		n = n->prev;
	}
}

t_array		p_solution(t_psolver *g)
{
	t_array	ops;

	ops = ft_ary_create(sizeof(t_op));
	collect(&ops, g->solved_left);
	collect(&ops, g->solved_right);
	return (ops);
}
