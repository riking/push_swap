/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/27 21:29:08 by kyork             #+#    #+#             */
/*   Updated: 2016/11/27 23:06:18 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "path.h"
#include <ft_guard.h>
#include <stdlib.h>

t_pnode		*p_newnode(t_pnode *parent, t_stack *newstack)
{
	t_pnode	*n;

	n = ft_memalloc(sizeof(t_pnode));
	if (!n)
	{
		stack_free(newstack);
		return (NULL);
	}
	n->prev = parent;
	n->depth = parent->depth + 1;
	n->from_solved = parent->from_solved;
	n->st = newstack;
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
