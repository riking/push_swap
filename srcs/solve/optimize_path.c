/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimize_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 15:46:05 by kyork             #+#    #+#             */
/*   Updated: 2016/12/10 19:11:02 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "path.h"
#include <stdlib.h>
#include <ft_printf.h>

/*
** This file takes a move sequence from a different solving method and runs it
** through the path solver to discover optimizations.
*/

static void		debug_print_node(t_pnode *n)
{
	t_pnode		*cur;

	cur = n;
	ft_dprintf(2, "Printing node %p. depth=%d from_solved=%d\n", n, n->opt_depth, n->from_solved);
	print_stack(n->st);
	ft_dprintf(2, "[n] < ");
	while (cur->prev)
	{
		ft_dprintf(2, "%s < ", op_name(cur->prev_op));
		cur = cur->prev;
	}
	ft_dprintf(2, "[start]\n");
}

static void		submitsolution(t_psolver *g, t_array *ops, t_stack *sto)
{
	t_pnode		*pn;
	t_pnode		*n;
	size_t		idx;

	idx = -1;
	pn = ft_memalloc(sizeof(t_pnode));
	pn->st = stack_clone(sto);
	p_submit(g, pn, &opt_onmatch);
	while (++idx < ops->item_count)
	{
		n = p_newnode(pn, *(t_op*)ft_ary_get(ops, idx));
		n->opt_depth = 0;
		debug_print_node(n);
		if (PSUB_PRUNE == p_submit(g, n, &opt_onmatch))
		{
			pn = p_findeq(g, n->st);
			p_freenode(n);
		}
		else
			pn = n;
	}
	ft_dprintf(2, "printing final parent node\n");
	debug_print_node(pn);
}

static void		rundepth(t_psolver *g, int depth)
{
	t_pnode		*p;

	while (g->workqueue.item_count > 0)
	{
		p = *(t_pnode**)ft_ary_get(&g->workqueue, g->workqueue.item_count - 1);
		ft_ary_poplast(&g->workqueue);
		if (p->opt_depth < depth)
			p_step(g, p, &opt_onmatch);
	}
}

void			debug_print_solution(t_psolver *g)
{
	t_pnode		*cur;
	t_stack		*clone;
	size_t		idx;

	cur = (g->solved_left->from_solved) ? g->solved_right : g->solved_left;
	idx = 0;
	clone = stack_clone(g->start);
	ft_dprintf(2, "Solution\n");
	print_stack(clone);
	ft_dprintf(2, "[start]");
	while (idx < cur->st->ops.item_count)
	{
		stack_do(clone, *(t_op*)ft_ary_get(&cur->st->ops, idx));
		ft_dprintf(2, " > %s", op_name(*(t_op*)ft_ary_get(&cur->st->ops, idx)));
		idx++;
	}
	ft_dprintf(2, " [join]\n");
	print_stack(clone);
	ft_dprintf(2, "[join]");
	cur = (g->solved_left->from_solved) ? g->solved_left : g->solved_right;
	idx = 0;
	while (idx < cur->st->ops.item_count)
	{
		stack_do(clone, op_inverse(*(t_op*)ft_ary_get(&cur->st->ops, cur->st->ops.item_count - 1 - idx)));
		ft_dprintf(2, " > %s", op_name(op_inverse(*(t_op*)ft_ary_get(&cur->st->ops, cur->st->ops.item_count - 1 - idx))));
		idx++;
	}
	ft_dprintf(2, "\n");
	print_stack(clone);
}

t_array			p_optimize(t_array ops, t_stack *st, t_stack *sorted)
{
	t_psolver	g;
	t_pnode		*pn;
	t_pnode		*n;
	t_array		solve;

	p_setup(&g);
	g.start = st;
	g.solved_left = 0;
	g.solved_right = 0;
	submitsolution(&g, &ops, st);
	n = p_findeq(&g, sorted);
	debug_print_node(n);
	rundepth(&g, 7);
	n = p_findeq(&g, sorted);
	g.solved_left = n;
	debug_print_node(n);
	pn = ft_memalloc(sizeof(t_pnode));
	pn->st = stack_clone(sorted);
	pn->from_solved = true;
	g.solved_right = pn;
	solve = p_solution(&g);
	p_free(&g);
	ft_ary_destroy(&ops);
	return (solve);
}
