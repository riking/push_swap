/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smallsort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/10 16:35:03 by kyork             #+#    #+#             */
/*   Updated: 2016/12/10 22:00:29 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "merge.h"

/*
** Smallsort returns the optimum sorting method if only swaps and rolls, not
** pushes, are allowed.
*/

int						req_cmp(t_sortreq req, int idx1, int idx2)
{
	int		val1;
	int		val2;

	val1 = stack_get(req.st, req.sd, idx1);
	val2 = stack_get(req.st, req.sd, idx2);
	return (req_cmp2(req, val1, val2));
}

int						req_cmp2(t_sortreq req, int val1, int val2)
{
	if (val1 < val2)
		return (req.inv ? 1 : -1);
	else if (val1 > val2)
		return (req.inv ? -1 : 1);
	return (0);
}

void					vals_to_patt(t_sortreq req, int *values, int *pattern)
{
	int		idx[2];

	idx[0] = -1;
	while (++idx[0] < req.size)
	{
		idx[1] = -1;
		while (++idx[1] < req.size)
			if (values[idx[1]] == stack_get(req.st, req.sd, -(1 + idx[0])))
				pattern[idx[0]] = idx[1] + 1;
	}
}

static const t_op		g_sort2_ops[] = {
	OP_INVALID,
	OP_SA,
};

t_array					small_sort2(t_sortreq req)
{
	if (1 == req_cmp(req, -1, -2))
		return (ft_ary_viewof((void*)&g_sort2_ops[1], 1, sizeof(t_op)));
	return (ft_ary_viewof((void*)&g_sort2_ops[0], 0, sizeof(t_op)));
}

t_array					small_sort(t_sortreq req)
{
	t_array	ary;
	t_array ret;
	t_op	op;
	int		i;

	if (req.size == 0 || req.size == 1)
		return (FT_ARY_NULL);
	if (req.size == 2)
		ary = small_sort2(req);
	if (req.size == 3)
		ary = small_sort3(req);
	if (req.size == 4)
		ary = small_sort4(req);
	ret = ft_ary_create(sizeof(t_op));
	ft_ary_grow(&ret, ary.item_count);
	i = -1;
	while (++i < (int)ary.item_count)
	{
		op = op_on(*(t_op*)ft_ary_get(&ary, i), req.sd);
		ft_ary_append(&ret, &op);
	}
	return (ret);
}
