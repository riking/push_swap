/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_sort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 15:12:05 by kyork             #+#    #+#             */
/*   Updated: 2016/11/28 17:15:13 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "help_best.h"

t_array		help_sort(t_stack *st, t_stack *sorted)
{
	ssize_t		bottomwrong;
	t_hsolver	g;
	t_array		ops;

	g.st = st;
	g.hrollidx = 0;
	g.hpushidx = 0;
	bottomwrong = 0;
	while (bottomwrong < (ssize_t)st->st_a.item_count &&
			h_getel(&g, H_MAIN, bottomwrong) == AGET(sorted, a, bottomwrong))
		bottomwrong++;
	h_main_to_help_best_start(&g, H_PUSH, H_ROLL, bottomwrong);
	h_push_to_main(&g, H_PUSH, -1);
	h_move_to_main(&g, H_ROLL, H_PUSH, -1);
	ops = ft_ary_clone(st->ops, 0);
	return (ops);
}
