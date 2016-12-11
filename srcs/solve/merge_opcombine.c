/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_opcombine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/10 18:03:43 by kyork             #+#    #+#             */
/*   Updated: 2016/12/10 22:42:09 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "merge.h"
#include <stdlib.h>
#include <ft_printf.h>

#define EVEN(x) ((x) % 2 == 0)

/*
** warning: mutates array.ptr, but that's okay since we take it by value
** in merge_ops
** => parent must ft_ary_destroy()
*/

#define REMONE(a) {*(t_op**)(&(a)->ptr) += 1; (a)->item_count--;}
#define PICKRET(a) do{op=*(t_op*)ft_ary_get(a,0);REMONE(a);return(op);}while(0)

static t_op		merged_op(t_op l, t_op r)
{
	if ((l == OP_SA && r == OP_SB) || (r == OP_SA && l == OP_SB))
		return (OP_SS);
	if ((l == OP_RA && r == OP_RB) || (r == OP_RA && l == OP_RB))
		return (OP_RR);
	if ((l == OP_RRA && r == OP_RRB) || (r == OP_RRA && l == OP_RRB))
		return (OP_RRR);
	return (OP_INVALID);
}

bool			m_is_locker(t_op op, t_side sd)
{
	if (op == OP_PA || op == OP_PB)
		return (true);
	if (op == OP_SS || op == OP_RR || op == OP_RRR)
		return (true);
	if (op_on(op, sd) != op)
		return (true);
	return (false);
}

static int		check_combine(t_array *m, t_array *iter, t_side mside)
{
	t_op	op;
	int		idx;

	op = *(t_op*)ft_ary_get(m, 0);
	idx = 0;
	while (idx < (int)iter->item_count)
	{
		if (OP_INVALID != merged_op(op, *(t_op*)ft_ary_get(iter, idx)))
			return (1);
		else if (m_is_locker(*(t_op*)ft_ary_get(iter, idx), !mside))
			return (-1);
		idx++;
	}
	return (0);
}

/*
** do not call if we are stack-locked
**
** if top(left) and top(right) are combinable:
**   consume both, return combined
** for both tops of opqueue:
**   search for a combinable op on the other opqueue
**     if found, consume & return top(other)
**     -> on the next iter, will do combining
** -> no combinables
** if left is a locker, use right
** use left
*/

t_op			merge_opcombine(t_array *left, t_array *right)
{
	t_op	op;
	int		sta;

	op = *(t_op*)ft_ary_get(left, 0);
	if (OP_INVALID != merged_op(op, *(t_op*)ft_ary_get(right, 0)))
	{
		op = merged_op(op, *(t_op*)ft_ary_get(right, 0));
		REMONE(left);
		REMONE(right);
		return (op);
	}
	sta = check_combine(left, right, ST_A);
	if (sta == 1)
		PICKRET(right);
	sta = check_combine(right, left, ST_B);
	if (sta == 1)
		PICKRET(left);
	if (m_is_locker(op, ST_A))
		PICKRET(right);
	PICKRET(left);
}

void			m_skip_lockers(t_array *ops, t_stack *st, t_array *pops,
					t_side sd)
{
	int		push;
	int		roll;
	t_op	op;

	push = 0;
	roll = 0;
	op = OP_INVALID;
	while (op == OP_INVALID || push != 0 || roll != 0)
	{
		if (pops->item_count == 0)
			abort();// NORM
		op = *(t_op*)ft_ary_get(pops, 0);
		ft_ary_append(ops, &op);
		stack_do(st, op);
		if (op == OP_PA || op == OP_PB)
			push += ((sd == ST_A) == (op == OP_PB)) ? 1 : -1;
		/*
		else if (op == OP_RR || op == ((sd == ST_A) ? OP_RB : OP_RA))
			roll += 1;
		else if (op == OP_RRR || op == ((sd == ST_A) ? OP_RRB : OP_RRA))
			roll -= 1;
			*/
		*(t_op**)&(pops->ptr) += 1;
		pops->item_count -= 1;
	}
}
