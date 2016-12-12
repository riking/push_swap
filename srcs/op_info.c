/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_info.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/10 16:26:34 by kyork             #+#    #+#             */
/*   Updated: 2016/12/12 15:29:34 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ps_stack.h"
#include <stdlib.h>

t_op		op_inverse(t_op op)
{
	if (op == OP_SA || op == OP_SB || op == OP_SS)
		return (op);
	if (op == OP_PA)
		return (OP_PB);
	if (op == OP_PB)
		return (OP_PA);
	if (op == OP_RA || op == OP_RB || op == OP_RR)
		return (op + OP_RRA - OP_RA);
	if (op == OP_RRA || op == OP_RRB || op == OP_RRR)
		return (op - OP_RRA + OP_RA);
	return (OP_INVALID);
}

/*
** note: doesn't really make sense for PA/PB
*/

t_op		op_on(t_op op, t_side stack)
{
	if (op == OP_SA || op == OP_SB || op == OP_SS)
		return (stack == ST_A ? OP_SA : OP_SB);
	if (op == OP_PA || op == OP_PB)
		return (stack == ST_A ? op : op_inverse(op));
	if (op == OP_RA || op == OP_RB || op == OP_RR)
		return (stack == ST_A ? OP_RA : OP_RB);
	if (op == OP_RRA || op == OP_RRB || op == OP_RRR)
		return (stack == ST_A ? OP_RRA : OP_RRB);
	return (OP_INVALID);
}

bool		is_sorted(t_stack *st)
{
	size_t	idx;
	int		last;

	last = AGET(st, a, 0);
	idx = 1;
	while (idx < st->st_a.item_count)
	{
		if (last < AGET(st, a, idx))
			return (false);
		last = AGET(st, a, idx);
		idx++;
	}
	return (true);
}

int			cmp_int(void *left, void *right, size_t size, void *data)
{
	int			*a;
	int			*b;
	uintptr_t	inverse;

	if (size != sizeof(int))
		exit(3);
	a = left;
	b = right;
	inverse = (uintptr_t)data;
	if (*a < *b)
		return (inverse ? -1 : 1);
	if (*a > *b)
		return (inverse ? 1 : -1);
	return (0);
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
