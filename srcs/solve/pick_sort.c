/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pick_sort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/11 00:05:33 by kyork             #+#    #+#             */
/*   Updated: 2016/12/11 00:41:03 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "merge.h"
#include <ft_guard.h>

static int	max_value(t_sortreq req)
{
	int max;
	int maxidx;
	int idx;

	max = stack_get(req.st, req.sd, -1);
	maxidx = -1;
	idx = 0;
	while (idx < req.size)
	{
		if (req_cmp(req, maxidx, -1 - idx) < 0)
		{
			maxidx = -1 - idx;
			max = stack_get(req.st, req.sd, maxidx);
		}
		idx++;
	}
	return (max);
}

t_array		pick_sort(t_sortreq req)
{
	while (req.size && stack_get(req.st, req.sd, -req.size) == max_value(req))
		req.size = req.size - 1;
	TGUARD(GFAIL(FT_ARY_NULL, 0), req.size == 0);
	if (req.size <= 4)
		return (small_sort(req));
	else
		return (merge_recurse(req, 2));
}

t_array		picked_sort(t_stack *st, t_stack *sorted)
{
	(void)sorted;
	return (pick_sort((t_sortreq){st, st->st_a.item_count, ST_A, false}));
}
