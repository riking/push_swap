/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_solve.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/27 23:18:17 by kyork             #+#    #+#             */
/*   Updated: 2016/11/28 17:03:11 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "path.h"
#include <stdlib.h>

void			p_setup(t_psolver *g)
{
	int		i;
	t_array	ary;

	g->hashtable = ft_ary_create(sizeof(t_array));
	i = -1;
	while (++i < HASH_BUCKETS)
	{
		ary = ft_ary_create(sizeof(t_pnode*));
		ft_ary_append(&g->hashtable, &ary);
	}
	g->workqueue = ft_ary_create(sizeof(t_pnode*));
	g->solved_left = 0;
	g->solved_right = 0;
}

static void		freebucket(void *item, size_t size)
{
	t_array	*bucket;

	if (size != sizeof(t_array))
		exit(3);
	bucket = item;
	ft_ary_foreach(bucket, &p_lfreenode);
}

void			p_free(t_psolver *g)
{
	g->solved_left = NULL;
	ft_ary_foreach(&g->hashtable, &freebucket);
	ft_ary_destroy(&g->hashtable);
	ft_ary_destroy(&g->workqueue);
	p_freenode(g->solved_right);
}

static int		add_initial(t_psolver *g, t_stack *st, t_stack *sorted)
{
	t_pnode		*p;

	p = ft_memalloc(sizeof(t_pnode));
	p->st = st;
	p_submit(g, p);
	p = ft_memalloc(sizeof(t_pnode));
	p->st = sorted;
	p->from_solved = true;
	return (p_submit(g, p));
}

t_array			p_do_solve(t_stack *st, t_stack *sorted)
{
	t_psolver	g;
	int			status;
	t_pnode		*p;
	t_array		solve;

	p_setup(&g);
	status = add_initial(&g, st, sorted);
	while (status != PSUB_MATCH && status != PSUB_ERROR)
	{
		p = *(t_pnode**)ft_ary_get(&g.workqueue, 0);
		ft_ary_remove(&g.workqueue, 0);
		status = p_step(&g, p);
	}
	solve = p_solution(&g);
	p_free(&g);
	return (solve);
}
