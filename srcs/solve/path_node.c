/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/27 21:29:08 by kyork             #+#    #+#             */
/*   Updated: 2016/12/05 13:35:57 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "path.h"
#include <stdlib.h>

t_pnode		*p_newnode(t_pnode *parent, t_op op)
{
	t_stack *st;
	t_pnode	*n;

	n = ft_memalloc(sizeof(t_pnode));
	if (!n)
		return (NULL);
	st = stack_clone(parent->st);
	if (!st)
	{
		free(n);
		return (NULL);
	}
	stack_do(st, op);
	n->prev = parent;
	n->prev_op = op;
	n->opt_depth = parent->opt_depth + 1;
	n->from_solved = parent->from_solved;
	n->st = st;
	return (n);
}

void		p_lfreenode(void *ptr, size_t size)
{
	t_pnode **n;

	if (size != sizeof(t_pnode*))
		exit(3);
	n = ptr;
	p_freenode(*n);
}

void		p_freenode(t_pnode *n)
{
	if (n)
		stack_free(n->st);
	free(n);
}

size_t		p_opcount(t_pnode *n)
{
	size_t	count;

	count = 0;
	while (n->prev)
	{
		count++;
		n = n->prev;
	}
	return (count);
}
