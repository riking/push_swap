/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_view.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 14:21:58 by kyork             #+#    #+#             */
/*   Updated: 2016/12/05 14:30:18 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "help_best.h"
#include <stdlib.h>

ssize_t		h_getcount(t_hsolver *g, int which)
{
	if (which == H_ROLL)
		return (g->hrollidx);
	if (which == H_PUSH)
	{
		if (g->hpushidx != (ssize_t)g->st->st_b.item_count)
			abort();// norm
		return (g->hpushidx);
	}
	return (g->st->st_a.item_count - g->hrollidx);
}

int			h_getel(t_hsolver *g, int which, ssize_t idx)
{
	if (which == H_PUSH)
		return (AGET(g->st, b, idx));
	if (which == H_ROLL)
	{
		return (AGET(g->st, a, g->hrollidx - 1 - idx));
	}
	// which == H_MAIN
	return (AGET(g->st, a, g->hrollidx + idx));
}
