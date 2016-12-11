/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_step.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/27 20:48:42 by kyork             #+#    #+#             */
/*   Updated: 2016/12/10 22:45:10 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "path.h"
#include <ft_printf.h>

#include <stdlib.h>

int			opt_onmatch(t_psolver *g, t_pnode *n, t_pnode *kn)
{
	size_t	n_c;
	size_t	kn_c;

	(void)g;
	if (n->from_solved || kn->from_solved)
		exit(5);
	n_c = p_opcount(n);
	kn_c = p_opcount(kn);
	if (n_c >= kn_c)
		return (PSUB_PRUNE);
	if (kn->opt_depth == 0)
	ft_dprintf(2, "Found improvement. new=(op=%3s, depth=%2d, count=%2ld) old=(op=%3s, depth=%2d, count=%2ld)\n", op_name(n->prev_op), n->opt_depth, n_c, op_name(kn->prev_op), kn->opt_depth, kn_c);
	kn->prev_op = n->prev_op;
	kn->prev = n->prev;
	ft_ary_destroy(&kn->st->ops);
	kn->st->ops = ft_ary_clone(n->st->ops, 1);
	return (PSUB_PRUNE);
}

int			path_onmatch(t_psolver *g, t_pnode *n, t_pnode *kn)
{
	if (kn->from_solved == n->from_solved)
	{
		return (PSUB_PRUNE);
	}
	ft_dprintf(2, "Found solution. left=(ops=%ld depth=%d) right=(ops=%ld depth=%d)\n", kn->st->ops.item_count, kn->opt_depth, n->st->ops.item_count, n->opt_depth);
	g->solved_left = kn;
	g->solved_right = n;
	debug_print_solution(g);
	return (PSUB_MATCH);
}

t_pnode		*p_findeq(t_psolver *g, t_stack *st)
{
	t_array		*known;
	t_pnode		*kn;
	ssize_t		idx;
	uint32_t	h;

	h = stack_hash(st);
	known = (t_array*)ft_ary_get(&g->hashtable, h % HASH_BUCKETS);
	idx = -1;
	while (++idx < (ssize_t)known->item_count)
	{
		kn = *(t_pnode**)ft_ary_get(known, idx);
		if (0 == stack_cmp(kn->st, st))
		{
			return (kn);
		}
	}
	return (NULL);
}

int			p_submit(t_psolver *g, t_pnode *n, t_matchfunc f)
{
	t_array		*bucket;
	t_pnode		*kn;

	kn = p_findeq(g, n->st);
	if (kn != NULL)
		return (f(g, n, kn));
	bucket = (t_array*)ft_ary_get(&g->hashtable,
			stack_hash(n->st) % HASH_BUCKETS);
	ft_ary_append(bucket, &n);
	ft_ary_append(&g->workqueue, &n);
	return (PSUB_OKAY);
}

int			p_step(t_psolver *g, t_pnode *n, t_matchfunc f)
{
	t_pnode	*nn;
	t_op	op;
	int		r;

	op = OP_INVALID;
	while (++op < OP_STOPITER)
	{
		if (op == OP_PB)
			continue; // REMOVE THIS
		nn = p_newnode(n, op);
		if (!nn)
			return (PSUB_ERROR);
		r = p_submit(g, nn, f);
		if (r == PSUB_PRUNE)
			p_freenode(nn);
		else if (r == PSUB_MATCH)
			return (PSUB_MATCH);
	}
	return (PSUB_OKAY);
}
