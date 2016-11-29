/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_step.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/27 20:48:42 by kyork             #+#    #+#             */
/*   Updated: 2016/11/28 16:31:34 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "path.h"
#include <ft_printf.h>

static int	p_onmatch(t_psolver *g, t_pnode *n, t_pnode *kn)
{
	if (kn->from_solved == n->from_solved)
	{
		if (n->st->ops.item_count < kn->st->ops.item_count)
		{
			ft_dprintf(2, "Found replacement\n");
			kn->prev = n->prev;
			ft_ary_destroy(&kn->st->ops);
			kn->st->ops = ft_ary_clone(n->st->ops, 0);
		}
		return (PSUB_PRUNE);
	}
	g->solved_left = kn;
	p_freenode(g->solved_right);
	g->solved_right = n;
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

int			p_submit(t_psolver *g, t_pnode *n)
{
	t_array		*bucket;
	t_pnode		*kn;

	kn = p_findeq(g, n->st);
	if (kn != NULL)
	{
		return (p_onmatch(g, n, kn));
	}
	bucket = (t_array*)ft_ary_get(&g->hashtable,
			stack_hash(n->st) % HASH_BUCKETS);
	ft_ary_append(bucket, &n);
	ft_ary_append(&g->workqueue, &n);
	return (PSUB_OKAY);
}

int			p_step(t_psolver *g, t_pnode *n)
{
	t_stack	*st;
	t_pnode	*nn;
	t_op	op;
	int		r;

	op = OP_INVALID;
	while (++op < OP_STOPITER)
	{
		st = stack_clone(n->st);
		stack_do(st, op);
		if (0 != stack_cmp(st, n->st))
		{
			nn = p_newnode(n, st);
			r = p_submit(g, nn);
			if (r == PSUB_PRUNE)
				p_freenode(nn);
			else if (r == PSUB_MATCH)
				return (PSUB_MATCH);
		}
		else
			stack_free(st);
	}
	return (PSUB_OKAY);
}
