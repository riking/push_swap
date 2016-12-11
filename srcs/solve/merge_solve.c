/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_solve.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/10 19:20:32 by kyork             #+#    #+#             */
/*   Updated: 2016/12/11 00:57:48 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "merge.h"
#include "path.h"

#include <ft_printf.h>

static void		merge_do(t_array *ops, t_stack *st, t_op op)
{
	ft_ary_append(ops, &op);
	stack_do(st, op);
}

void			merge_combine(t_cmreq req, t_stack *st, t_array *ops)
{
	t_op	op;

	while (req.l.item_count > 0 && req.r.item_count > 0)
	{
		if (m_is_locker(*(t_op*)ft_ary_get(&req.r, 0), !req.sd))
			m_skip_lockers(ops, st, &req.r, !req.sd);
		else if (m_is_locker(*(t_op*)ft_ary_get(&req.l, 0), req.sd))
			m_skip_lockers(ops, st, &req.l, req.sd);
		else
		{
			if (req.sd == ST_A)
				op = merge_opcombine(&req.l, &req.r);
			else
				op = merge_opcombine(&req.r, &req.l);
			merge_do(ops, st, op);
		}
	}
	while (req.l.item_count > 0)
		m_skip_lockers(ops, st, &req.l, req.sd);
	while (req.r.item_count > 0)
		m_skip_lockers(ops, st, &req.r, !req.sd);
}

static t_cmreq	make_cmreq(t_side sd, t_array *left, t_array *right)
{
	t_cmreq	req;

	req.l = *left;
	req.r = *right;
	req.sd = sd;
	return (req);
}

static bool		m_is_sorted(t_sortreq req)
{
	int			idx;

	idx = 1;
	while (idx < (int)req.size)
	{
		if (req_cmp(req, -idx, -idx - 1) >= 0)
			return (false);
		idx++;
	}
	return (true);
}

static int		prep_recurse(t_sortreq req, t_stack *st, t_array *opsary)
{
	int		idx;

	idx = req.size / 2;
	while (idx-- > 0)
		merge_do(&opsary[2], st, op_on(OP_PB, req.sd));
	opsary[0] = pick_sort((t_sortreq){st, req.size - (int)(req.size / 2),
			req.sd, req.inv});
	opsary[1] = pick_sort((t_sortreq){st, req.size / 2, !req.sd, !req.inv});
	return (0);
}

#include <stdlib.h>

t_array			merge_recurse(t_sortreq req, int variation)
{
	t_stack		*st;
	t_array		ops[3];
	int			rolls;

	st = stack_clone(req.st);
	ops[2] = ft_ary_create(sizeof(t_op));
	rolls = prep_recurse(req, st, ops);
	merge_combine(make_cmreq(req.sd, &ops[0], &ops[1]), st, &ops[2]);
	(void)variation;
	merge_merge(req, &ops[2], st, rolls);
	while (rolls-- > 0)
		merge_do(&ops[2], st, op_on(OP_RRA, req.sd));
	t_stack *tmp = req.st;
	req.st = st;
	if (!m_is_sorted(req))
		abort();
	req.st = tmp;
	ops[2] = p_optimize(ops[2], req.st, st, 1);
	stack_free(st);
	ft_ary_destroy(&ops[0]);
	ft_ary_destroy(&ops[1]);
	return (ops[2]);
}
