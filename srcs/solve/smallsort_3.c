/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smallsort_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/10 17:23:31 by kyork             #+#    #+#             */
/*   Updated: 2016/12/10 17:46:54 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "merge.h"
#include <stdlib.h>

#define OP_IV OP_INVALID

static const t_op	g_sort3_ops[] = {
	OP_IV, OP_IV, OP_IV, OP_IV, OP_IV,
	OP_SA, OP_IV, OP_IV, OP_IV, OP_IV,
	OP_RA, OP_SA, OP_RRA, OP_IV, OP_IV,
	OP_RA, OP_SA, OP_RRA, OP_SA, OP_IV,
	OP_SA, OP_RA, OP_SA, OP_RRA, OP_IV,
	OP_SA, OP_RA, OP_SA, OP_RRA, OP_SA,
};

#define OPS_STRIDE 5

static const int	g_sort3_ops_len[] = {
	0,
	1,
	3,
	4,
	4,
	5,
};

static const int	g_sort3_pattern[] = {
	1, 2, 3,
	2, 1, 3,
	1, 3, 2,
	2, 3, 1,
	3, 1, 2,
	3, 2, 1,
};

#define PATTERN_STRIDE 3

t_array				small_sort3(t_sortreq req)
{
	int		values[3];
	int		pattern[3];
	int		idx[2];
	t_array	a;

	values[0] = stack_get(req.st, req.sd, -1);
	values[1] = stack_get(req.st, req.sd, -2);
	values[2] = stack_get(req.st, req.sd, -3);
	a = ft_ary_viewof(values, 3, sizeof(int));
	ft_ary_sort(&a, &cmp_int, NULL);
	vals_to_patt(req, values, pattern);
	idx[0] = -1;
	while (++idx[0] < ARRAYLEN(g_sort3_pattern))
		if (0 == ft_memcmp(pattern, &g_sort3_pattern[idx[0] * PATTERN_STRIDE],
					sizeof(pattern)))
		{
			a = ft_ary_viewof((void*)&g_sort3_ops[idx[0] * OPS_STRIDE],
					g_sort3_ops_len[idx[0]], sizeof(t_op));
			return (a);
		}
	exit(5);
	return (FT_ARY_NULL);
}
