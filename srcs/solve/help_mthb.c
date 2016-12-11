/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_mthb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/27 23:42:30 by kyork             #+#    #+#             */
/*   Updated: 2016/12/10 19:14:25 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "help_best.h"
#include <libft.h>
#include "../../includes/libft.h"
#include "../../includes/ft_guard.h"
#include <stdint.h>

#define GRET(expr) {(void)(expr); return;}

static ssize_t	find_largest(t_hsolver *g, size_t offset, int64_t *maxp)
{
	ssize_t	idx;
	int64_t	max;
	size_t	main_len;
	int		el;

	idx = -1;
	max = -1000000000LL;
	main_len = h_getcount(g, H_MAIN);
	while (offset < main_len)
	{
		el = h_getel(g, H_MAIN, offset);
		if (el >= max)
		{
			idx = offset;
			max = el;
		}
		offset++;
	}
	*maxp = max;
	return (idx);
}

void			h_main_to_help_best(t_hsolver *g, int dst, int helper,
				size_t offset)
{
	ssize_t		idx;
	int64_t		max_el;
	int			top_count;

	TGUARD(GRET(0), offset >= (size_t)h_getcount(g, H_MAIN));
	idx = find_largest(g, offset, &max_el);
	while (idx >= (ssize_t)offset)
	{
		TGUARD(GCONT(idx--), h_getel(g, H_MAIN, idx) < max_el);
		top_count = h_getcount(g, H_MAIN) - idx - 1;
		h_main_to_help_best(g, helper, dst, idx + 1);
		h_move(g, H_MAIN, dst);
		h_push_to_main(g, helper, top_count);
		idx--;
	}
	h_main_to_help_best(g, dst, helper, offset);
}

void			h_main_to_help_best_start(t_hsolver *g, int dst, int helper,
				size_t offset)
{
	ssize_t		idx;
	int64_t		max_el;
	int			top_count;

	TGUARD(GRET(0), offset >= (size_t)h_getcount(g, H_MAIN));
	idx = find_largest(g, offset, &max_el);
	while (idx >= (ssize_t)offset)
	{
		TGUARD(GCONT(idx--), h_getel(g, H_MAIN, idx) < max_el);
		top_count = h_getcount(g, H_MAIN) - idx - 1;
		h_main_to_help_best(g, helper, dst, idx + 1);
		h_move(g, H_MAIN, dst);
		h_push_to_main(g, helper, top_count);
		idx--;
	}
	h_main_to_help_best(g, helper, dst, offset);
}
