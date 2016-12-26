/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_merge.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/10 20:14:33 by kyork             #+#    #+#             */
/*   Updated: 2016/12/11 00:58:31 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "merge.h"

static void	merge_do(t_op op, t_array *ops, t_stack *st, int *dec)
{
	ft_ary_append(ops, &op);
	stack_do(st, op);
	if (dec)
		*dec -= 1;
}

void		merge_merge(t_sortreq req, t_array *ops, t_stack *st, int rolls)
{
	int			size[2];

	size[1] = req.size / 2;
	size[0] = 0;
	while (size[0] < req.size - size[1] - rolls && req_cmp2(req, stack_get(st,
			req.sd, -1), stack_get(st, !req.sd, -1)) < 0)
	{
		merge_do(op_on(OP_RA, req.sd), ops, st, 0);
		size[0]++;
	}
	while (size[0] > 0 && size[1] > 0)
		if (req_cmp2(req, stack_get(st, req.sd, 0),
					stack_get(st, !req.sd, -1)) > 0)
		{
			merge_do(op_on(OP_RRA, req.sd), ops, st, &size[0]);
		}
		else
		{
			merge_do(op_on(OP_PA, req.sd), ops, st, &size[1]);
		}
	while (size[0]-- > 0)
		merge_do(op_on(OP_RRA, req.sd), ops, st, 0);
	while (size[1]-- > 0)
		merge_do(op_on(OP_PA, req.sd), ops, st, 0);
}
