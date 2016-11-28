/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_solve.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/27 23:18:17 by kyork             #+#    #+#             */
/*   Updated: 2016/11/27 23:27:20 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "path.h"

static void		setup(t_psolver *g)
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

	setup(&g);
	status = add_initial(&g, st, sorted);
	while (status != PSUB_MATCH && status != PSUB_ERROR)
	{
		p = *(t_pnode**)ft_ary_get(&g.workqueue, 0);
		ft_ary_remove(&g.workqueue, 0);
		status = p_step(&g, p);
	}
	return (p_solution(&g));
}
