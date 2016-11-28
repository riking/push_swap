/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_mthb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/27 23:42:30 by kyork             #+#    #+#             */
/*   Updated: 2016/11/28 00:06:31 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "help_best.h"
#include <libft.h>
#include "../../includes/libft.h"
#include "../../includes/ft_guard.h"
#include <stdint.h>

#define GRET(expr) {(void)(expr); return;}

static ssize_t	find_largest(t_array main, size_t offset, int64_t *maxp)
{
	ssize_t	idx;
	int64_t	max;
   
	idx = -1;
	max = -1000000000LL;
	while (offset < main.item_count)
	{
		if (RGET(&main, offset) >= max)
		{
			idx = offset;
			max = RGET(&main, offset);
		}
		offset++;
	}
	*maxp = max;
	return (idx);
}

void			h_main_to_help_best(t_hsolver *g, int dst, int helper,
				size_t offset)
{
	t_array		main;
	ssize_t		idx;
	int64_t		max_el;
	int			top_count;

	main = h_getview(g, 0);
	TGUARD(GRET(0), offset >= main.item_count);
	idx = find_largest(main, offset, &max_el);
	while (idx >= (ssize_t)offset)
	{
		TGUARD(GCONT(0), RGET(&main, idx) < max_el);
		top_count = main.item_count - idx - 1;
		h_main_to_help_best(g, helper, dst, idx + 1);
		h_move(g, H_MAIN, dst);
		h_push_to_main(g, helper, top_count);
		main = h_getview(g, H_MAIN);
		idx--;
	}
	h_main_to_help_best(g, dst, helper, offset);
}

void			h_main_to_help_best_start(t_hsolver *g, int dst, int helper,
				size_t offset)
{
	t_array		main;
	ssize_t		idx;
	int64_t		max_el;
	int			top_count;

	main = h_getview(g, 0);
	TGUARD(GRET(0), offset >= main.item_count);
	idx = find_largest(main, offset, &max_el);
	while (idx >= (ssize_t)offset)
	{
		TGUARD(GCONT(0), RGET(&main, idx) < max_el);
		top_count = main.item_count - idx - 1;
		h_main_to_help_best(g, helper, dst, idx + 1);
		h_move(g, H_MAIN, dst);
		h_push_to_main(g, helper, top_count);
		main = h_getview(g, H_MAIN);
		idx--;
	}
	h_main_to_help_best(g, helper, dst, offset);
}
