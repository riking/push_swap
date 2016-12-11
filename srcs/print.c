/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/27 16:48:34 by kyork             #+#    #+#             */
/*   Updated: 2016/12/10 19:08:21 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ps_stack.h"
#include <libft.h>
#include <ft_printf.h>
#include <stdint.h>

#include "colors.inc"

/*
** credit to http://stackoverflow.com/a/12996028/1210278 for the mixer
*/

uint32_t			mixhash(uint32_t x)
{
	x = ((x >> 16) ^ x) * 0x45d9f3b;
	x = ((x >> 16) ^ x) * 0x45d9f3b;
	x = (x >> 16) ^ x;
	return (x);
}

static const char	*color(int val)
{
	int idx;

	idx = mixhash(val) % 216;
	return (&COLORTAB[idx * COLORSTRIDE]);
}

#define RESET "\033[m"

void				print_stack(t_stack *st)
{
	size_t	idx;
	int		width;

	idx = 0;
	width = 1;
	while (idx < st->st_a.item_count)
		width = MAX(width, ft_snprintf(0, 0, "%d",
					*(int*)ft_ary_get(&st->st_a, idx++)));
	idx = MAX(st->st_a.item_count, st->st_b.item_count);
	while (idx-- > 0)
	{
		if (idx >= st->st_a.item_count)
			ft_dprintf(2, "%*s %s%*d" RESET "\n", width, "",
					color(AGET(st, b, idx)), width, AGET(st, b, idx));
		else if (idx >= st->st_b.item_count)
			ft_dprintf(2, "%s%*d" RESET " %*s\n", color(AGET(st, a, idx)),
					width, AGET(st, a, idx), width, "");
		else
			ft_dprintf(2, "%s%*d" RESET" %s%*d" RESET "\n", color(AGET(st, a,
					idx)), width, AGET(st, a, idx), color(AGET(st, b, idx)),
					width, AGET(st, b, idx));
	}
	ft_dprintf(2, "%.*s %.*s\n", width, "------------", width, "------------");
	ft_dprintf(2, "%*s %*s\n", width, "a", width, "b");
}
