/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_move.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 13:05:57 by kyork             #+#    #+#             */
/*   Updated: 2016/11/28 15:45:06 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "help_best.h"

#define MDO_ADD 1
#define MDO_SKIP 2

static void	undoidx(t_hsolver *g, t_op insert, size_t count)
{
	t_array	holding;

	holding = ft_ary_create(sizeof(t_op));
	ft_ary_grow(&holding, count);
	while (count-- > 0)
	{
		ft_ary_append(&holding, ft_ary_get(&g->st->ops, g->st->ops.item_count - 1));
		stack_undo(g->st);
	}
	if (insert != OP_INVALID)
		stack_do(g->st, insert);
	ft_ary_poplast(&holding);
	while (holding.item_count > 0)
	{
		insert = *(t_op*)ft_ary_get(&holding, holding.item_count - 1);
		stack_do(g->st, insert);
		ft_ary_poplast(&holding);
	}
}

static int	h_move_rollcombine(t_hsolver *g, t_op cur, t_op op, size_t count)
{
	if ((cur == OP_RB && op == OP_RA) || (cur == OP_RRB && op == OP_RRA))
	{
		undoidx(g, (op == OP_RA) ? OP_RR : OP_RRR, count);
		return (MDO_SKIP);
	}
	if ((cur == OP_RRR && op == OP_RA) || (cur == OP_RR && op == OP_RRA))
	{
		undoidx(g, (op == OP_RA) ? OP_RB : OP_RRB, count);
		return (MDO_SKIP);
	}
	return (0);
}

static int	h_move_do(t_hsolver *g, t_op op)
{
	ssize_t	count;
	int		status;
	t_op	cur;

	count = 1;
	while (1)
	{
		if (((ssize_t)g->st->ops.item_count) - count < 0)
			return (MDO_ADD);
		cur = *(t_op*)ft_ary_get(&g->st->ops, g->st->ops.item_count - count);
		if (cur == op_inverse(op))
		{
			undoidx(g, OP_INVALID, count);
			stack_undo(g->st);
			return (MDO_SKIP);
		}
		if (cur == op)
			return (MDO_ADD);
		status = h_move_rollcombine(g, cur, op, count);
		if (status != 0)
			return (status);
		return (MDO_ADD);
	}
}

static void	apply(t_hsolver *g, t_op op, int status)
{
	status = h_move_do(g, op);
	if (status == MDO_ADD)
		stack_do(g->st, op);
}

void		h_move(t_hsolver *g, int src, int dst)
{
	size_t	check_last;

	check_last = g->st->ops.item_count;
	if (src == H_ROLL)
		apply(g, OP_RRA, g->hrollidx--);
	if (src == H_PUSH)
		apply(g, OP_PA, g->hpushidx--);
	if (dst == H_ROLL)
		apply(g, OP_RA, g->hrollidx++);
	if (dst == H_PUSH)
		apply(g, OP_PB, g->hpushidx++);
}
