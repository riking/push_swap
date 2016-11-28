/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/27 21:10:39 by kyork             #+#    #+#             */
/*   Updated: 2016/11/27 22:07:29 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ps_stack.h"
#include <stdlib.h>

void		stack_free(t_stack *st)
{
	if (st)
	{
		ft_ary_destroy(&st->st_a);
		ft_ary_destroy(&st->st_b);
		ft_ary_destroy(&st->ops);
		free(st);
	}
}

t_stack		*stack_clone(t_stack *s)
{
	t_stack	*st;
	size_t	size;

	size = s->st_a.item_count + s->st_b.item_count;
	st = ft_memalloc(sizeof(t_stack));
	st->st_a = ft_ary_clone(s->st_a, size);
	st->st_b = ft_ary_clone(s->st_b, size);
	st->ops = ft_ary_clone(s->ops, 4);
	return (st);
}

int			stack_cmp(t_stack *l, t_stack *r)
{
	size_t	idx;

	if (l->st_a.item_count != r->st_a.item_count)
		return ((l->st_a.item_count < r->st_a.item_count) ? -1 : 1);
	idx = 0;
	while (idx < l->st_a.item_count)
	{
		if (AGET(l, a, idx) != AGET(r, a, idx))
			return ((AGET(l, a, idx) < AGET(r, a, idx)) ? -1 : 1);
		idx++;
	}
	idx = 0;
	while (idx < l->st_b.item_count)
	{
		if (AGET(l, b, idx) != AGET(r, b, idx))
			return ((AGET(l, b, idx) < AGET(r, b, idx)) ? -1 : 1);
		idx++;
	}
	return (0);
}

uint32_t	stack_hash(t_stack *st)
{
	uint32_t	hash;
	size_t		idx;

	hash = 17;
	idx = 0;
	while (idx < st->st_a.item_count)
	{
		hash += AGET(st, a, idx);
		hash *= 31;
		idx++;
	}
	hash *= 31;
	idx = 0;
	while (idx < st->st_b.item_count)
	{
		hash += AGET(st, b, idx);
		hash *= 31;
		idx++;
	}
	return (mixhash(hash));
}
