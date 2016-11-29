/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimize_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 15:46:05 by kyork             #+#    #+#             */
/*   Updated: 2016/11/28 16:44:40 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "path.h"
#include <stdlib.h>

/*
** This file takes a move sequence from a different solving method and runs it
** through the path solver to discover optimizations.
*/

static void		submitsolution(t_psolver *g, t_array *ops, t_stack *sto)
{
	t_stack 	*st;
	t_pnode		*pn;
	t_pnode		*n;
	size_t		idx;

	idx = -1;
	pn = ft_memalloc(sizeof(t_pnode));
	pn->st = stack_clone(sto);
	p_submit(g, pn);
	while (++idx < ops->item_count)
	{
		st = stack_clone(pn->st);
		stack_do(st, *(t_op*)ft_ary_get(ops, idx));
		n = p_newnode(pn, st);
		if (PSUB_PRUNE == p_submit(g, n))
		{
			pn = p_findeq(g, st);
			p_freenode(n);
		}
		else
			pn = n;
	}
}

static void		rundepth(t_psolver *g, int depth)
{
	t_pnode		*p;

	while (g->workqueue.item_count > 0)
	{
		p = *(t_pnode**)ft_ary_get(&g->workqueue, 0);
		ft_ary_remove(&g->workqueue, 0);
		if (p->depth < depth)
			p_step(g, p);
	}
}

t_array			p_optimize(t_array ops, t_stack *st, t_stack *sorted)
{
	t_psolver	g;
	t_pnode		*pn;
	t_array		solve;

	p_setup(&g);
	pn = ft_memalloc(sizeof(t_pnode));
	pn->st = stack_clone(sorted);
	pn->from_solved = true;
	p_submit(&g, pn);
	submitsolution(&g, &ops, st);
	if (g.solved_right == NULL)
		exit(3);
	rundepth(&g, 5);
	solve = p_solution(&g);
	p_free(&g);
	return (solve);
}
