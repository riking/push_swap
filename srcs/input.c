/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/27 15:32:21 by kyork             #+#    #+#             */
/*   Updated: 2016/11/27 22:27:43 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <ft_guard.h>
#include "ps_stack.h"

#include <errno.h>
#include <stdlib.h>

static void		cl(t_stack *st)
{
	if (st)
	{
		ft_ary_destroy(&st->st_a);
		ft_ary_destroy(&st->st_b);
		ft_ary_destroy(&st->ops);
		free(st);
	}
}

static t_stack	*stack_new(void)
{
	t_stack	*st;

	NGUARD(GFAIL(NULL, cl(0)), st = ft_memalloc(sizeof(t_stack)));
	st->st_a = ft_ary_create(sizeof(int));
	NGUARD(GFAIL(NULL, cl(st)), st->st_a.ptr);
	st->st_b = ft_ary_create(sizeof(int));
	NGUARD(GFAIL(NULL, cl(st)), st->st_b.ptr);
	st->ops = ft_ary_create(sizeof(t_op));
	NGUARD(GFAIL(NULL, cl(st)), st->ops.ptr);
	return (st);
}

t_stack			*read_input(int argc, char **argv)
{
	t_stack *st;
	int		q;
	int		i;

	NGUARD(GFAIL(NULL, 0), st = stack_new());
	while (--argc >= 1)
	{
		errno = 0;
		q = ft_atoi(argv[argc]);
		ZGUARD(GFAIL(NULL, cl(st)), errno);
		i = -1;
		while (++i < (ssize_t)st->st_a.item_count)
			if (*(int*)ft_ary_get(&st->st_a, i) == q)
				GFAIL(NULL, cl(st));
		ZGUARD(GFAIL(NULL, cl(st)), ft_ary_append(&st->st_a, &q));
	}
	return (st);
}
