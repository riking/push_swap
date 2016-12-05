/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_solve.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/27 22:11:22 by kyork             #+#    #+#             */
/*   Updated: 2016/12/05 13:56:26 by kyork            ###   ########.fr       */
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

const char	*op_name(t_op op)
{
	if (op == OP_SA)
		return ("sa");
	if (op == OP_SB)
		return ("sb");
	if (op == OP_SS)
		return ("ss");
	if (op == OP_PA)
		return ("pa");
	if (op == OP_PB)
		return ("pb");
	if (op == OP_RA)
		return ("ra");
	if (op == OP_RB)
		return ("rb");
	if (op == OP_RR)
		return ("rr");
	if (op == OP_RRA)
		return ("rra");
	if (op == OP_RRB)
		return ("rrb");
	if (op == OP_RRR)
		return ("rrr");
	return ("(bad)");
}
