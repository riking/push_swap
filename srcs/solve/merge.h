/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/10 16:15:28 by kyork             #+#    #+#             */
/*   Updated: 2016/12/10 19:09:06 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MERGE_H
# define MERGE_H

# include "../ps_stack.h"
# include <stdbool.h>

typedef struct	s_sortreq {
	t_stack		*st;
	int			size;
	t_side		sd;
	bool		inv;
}				t_sortreq;

/*
** req_cmp compares two stack indices in the context of a sortreq
**
** if called with stack_get() -1, -2 then a negative return == sorted
*/
int				req_cmp(t_sortreq req, int idx1, int idx2);

void			vals_to_patt(t_sortreq req, int *values, int *pattern);

/*
** small_sort returns an ALLOCATED t_op array with the ops needed to sort the
** request
**
** small_sort2, 3, 4 return a VIEWOF CONST t_op array with the ops needed to
** sort as if the request was on the A stack
**
** client code should use small_sort and not the size-specific functions
*/
t_array			small_sort(t_sortreq req);
t_array			small_sort2(t_sortreq req);
t_array			small_sort3(t_sortreq req);
t_array			small_sort4(t_sortreq req);

bool			m_is_locker(t_op op, t_side sd);
t_op			merge_opcombine(t_array *left, t_array *right);
void			merge_ops(t_sortreq req, t_array left, t_array right);

#endif
