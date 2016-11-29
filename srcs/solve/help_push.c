/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_push.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 14:35:56 by kyork             #+#    #+#             */
/*   Updated: 2016/11/28 15:05:11 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "help_best.h"

void		h_push_to_main(t_hsolver *g, int src, int count)
{
	if (count == -1 && src == H_ROLL)
		count = g->hrollidx;
	else if (count == -1 && src == H_PUSH)
		count = g->hpushidx;
	while (count-- > 0)
		h_move(g, src, H_MAIN);
}

void		h_push_to_help(t_hsolver *g, int src, int dst, int count)
{
	if (count == -1)
		count = h_getcount(g, src);
	while (count-- > 0)
		h_move(g, src, dst);
}

void		h_help_to_help(t_hsolver *g, int src, int dst, int count)
{
	ssize_t		src_len;
	int			base_el;	
	ssize_t		base_idx;

	src_len = h_getcount(g, src);
	if (count == -1)
		count = src_len;
	if (count == 0)
		return ;
	base_el = h_getel(g, src, src_len - count);
	base_idx = src_len - count + 1;
	while (base_idx < src_len && base_el == h_getel(g, src, base_idx))
		base_idx++;
	h_push_to_main(g, src, src_len - base_idx);
	h_push_to_help(g, src, dst, base_idx + count - src_len);
	h_push_to_help(g, H_MAIN, dst, src_len - base_idx);
}

void		h_move_to_main(t_hsolver *g, int src, int help, int count)
{
	ssize_t		src_len;
	int			base_el;
	ssize_t		base_idx;

	src_len = h_getcount(g, src);
	if (count == -1)
		count = src_len;
	if (count == 0)
		return ;
	base_el = h_getel(g, src, src_len - count);
	base_idx = src_len - count + 1;
	while (base_idx < src_len && base_el == h_getel(g, src, base_idx))
		base_idx++;
	h_help_to_help(g, src, help, src_len - base_idx);
	h_push_to_main(g, src, base_idx + count - src_len);
	h_move_to_main(g, help, src, src_len - base_idx);
}
