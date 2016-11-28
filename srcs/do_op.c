/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_op.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/27 16:27:11 by kyork             #+#    #+#             */
/*   Updated: 2016/11/27 22:15:39 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ps_stack.h"

#define MODE_TOP 1
#define MODE_BOT 2

static void		swap_top(t_array *ary)
{
	if (ary->item_count <= 1)
		return ;
	ft_ary_swap(ary, ary->item_count - 2, ary->item_count - 1);
}

static void		move(t_array *src, int srcmode, t_array *dst, int dstmode)
{
	int		tmp;
	size_t	idx;

	if (src->item_count == 0)
		return ;
	if (srcmode == MODE_TOP)
		idx = src->item_count - 1;
	else
		idx = 0;
	tmp = *(int*)ft_ary_get(src, idx);
	ft_ary_remove(src, idx);
	if (dstmode == MODE_TOP)
		ft_ary_append(dst, &tmp);
	else
		ft_ary_insert(dst, &tmp, 0);
}

void	stack_do(t_stack *st, t_op op)
{
	if (op == OP_SA || op == OP_SS)
		swap_top(&st->st_a);
	if (op == OP_SB || op == OP_SS)
		swap_top(&st->st_b);
	if (op == OP_RA || op == OP_RR)
		move(&st->st_a, MODE_TOP, &st->st_a, MODE_BOT);
	if (op == OP_RB || op == OP_RR)
		move(&st->st_b, MODE_TOP, &st->st_b, MODE_BOT);
	if (op == OP_RRA || op == OP_RRR)
		move(&st->st_a, MODE_BOT, &st->st_a, MODE_TOP);
	if (op == OP_RRB || op == OP_RRR)
		move(&st->st_b, MODE_BOT, &st->st_b, MODE_TOP);
	if (op == OP_PA)
		move(&st->st_b, MODE_TOP, &st->st_a, MODE_TOP);
	if (op == OP_PB)
		move(&st->st_a, MODE_TOP, &st->st_b, MODE_TOP);
	ft_ary_append(&st->ops, &op);
}

t_op	op_inverse(t_op op)
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

void	stack_undo(t_stack *st)
{
	t_op	op;

	if (st->ops.item_count == 0)
		return ;
	op = *(t_op*)ft_ary_get(&st->ops, st->ops.item_count - 1);
	ft_ary_remove(&st->ops, st->ops.item_count - 1);
	if (op == OP_SA || op == OP_SS)
		swap_top(&st->st_a);
	if (op == OP_SB || op == OP_SS)
		swap_top(&st->st_b);
	if (op == OP_RRA || op == OP_RRR)
		move(&st->st_a, MODE_TOP, &st->st_a, MODE_BOT);
	if (op == OP_RRB || op == OP_RRR)
		move(&st->st_b, MODE_TOP, &st->st_b, MODE_BOT);
	if (op == OP_RA || op == OP_RR)
		move(&st->st_a, MODE_BOT, &st->st_a, MODE_TOP);
	if (op == OP_RB || op == OP_RR)
		move(&st->st_b, MODE_BOT, &st->st_b, MODE_TOP);
	if (op == OP_PB)
		move(&st->st_b, MODE_TOP, &st->st_a, MODE_TOP);
	if (op == OP_PA)
		move(&st->st_a, MODE_TOP, &st->st_b, MODE_TOP);
}
