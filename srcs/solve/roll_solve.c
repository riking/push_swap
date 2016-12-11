/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   roll_solve.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 13:58:09 by kyork             #+#    #+#             */
/*   Updated: 2016/12/10 19:16:05 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "roll.h"
#include <ft_printf.h>

static int		r_get(t_rsolver *g, int idx)
{
	ft_dprintf(2, ">r_get(size=%ld roll=%d idx=%d)\n", g->size, g->rollidx, idx);
	//idx -= g->rollidx;
	if (idx < 0)
		idx += g->size;
	if (idx < 0)
		idx += g->size;
	if (idx >= (int)g->size)
		idx -= g->size;
	if (idx >= (int)g->size)
		idx -= g->size;
	ft_dprintf(2, "<r_get aryidx = %d\n", idx);
	return AGET(g->st, a, idx);
}

static void		r_rollone(t_rsolver *g, int dir)
{
	if (g->st->st_a.item_count < 2)
		return ;
	if (dir == 1)
	{
		if ((r_get(g, -1) > r_get(g, -2)) == (g->rollidx != g->size - 1))
		{
			ft_dprintf(2, "%d > %d, swapping\n", r_get(g, -1), r_get(g, -2));
			stack_do(g->st, OP_SA);
		}
		stack_do(g->st, OP_RA);
		g->rollidx++;
		if (g->rollidx >= (int)g->size)
			g->rollidx -= g->size;
	}
	else
	{
		stack_do(g->st, OP_RRA);
		g->rollidx--;
		if (g->rollidx < 0)
			g->rollidx += g->size;
		if (g->rollidx != g->size - 1)
			if (r_get(g, -1) > r_get(g, -2))
				stack_do(g->st, OP_SA);
	}
}

t_array			roll_solve(t_stack *st, t_stack *sorted)
{
	t_rsolver	g;
	t_array		ops;
	ssize_t		i;

	g.st = st;
	g.size = sorted->st_a.item_count;
	g.rollidx = 0;
	g.swap_needs = NULL;
	i = 0;
	while (i < g.size * g.size)
	{
		if (g.rollidx == 0)
			if (is_sorted(g.st))
				break ;
		r_rollone(&g, 1);
		i++;
	}
	ops = ft_ary_clone(g.st->ops, 1);
	return (ops);
}
