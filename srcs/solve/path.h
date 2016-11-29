/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/27 20:28:58 by kyork             #+#    #+#             */
/*   Updated: 2016/11/28 16:00:09 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PATH_H
# define PATH_H

# include "../ps_stack.h"
# include <stdbool.h>

/*
** Path Solver
**
** Work forwards and backwards from the input and the solved state.
** When the two directions meet, a solution has been found.
**
** Hashtable: t_array[16]<t_array<*t_pnode>>
**     call p_hashstack, take bottom 4 bits, is index into 1st array
** Known: t_array<*t_pnode>
**
** Workqueue: t_array<*t_pnode>
**     insert with append(), pop with remove(0)
**
** To walk a node tree: use n->st->ops[last], n = n->prev
**     if n->from_solved, need to use inverse of op
*/

typedef struct	s_pnode {
	t_stack			*st;
	struct s_pnode	*prev;
	int				depth;
	bool			from_solved;
}				t_pnode;

# define HASH_BUCKETS 16

typedef struct	s_psolver {
	t_array		hashtable;
	t_array		workqueue;

	t_pnode		*solved_left;
	t_pnode		*solved_right;
}				t_psolver;

t_pnode			*p_newnode(t_pnode *parent, t_stack *newstack);
void			p_lfreenode(void *n, size_t size);
void			p_freenode(t_pnode *n);

# define PSUB_ERROR -1
# define PSUB_OKAY  0
# define PSUB_PRUNE 1
# define PSUB_MATCH 2

/*
** if p_submit returns PSUB_PRUNE, the caller must free the pnode it provided.
** otherwise, the provided pnode is retained in the hashtable or solved_right.
*/
int				p_submit(t_psolver *g, t_pnode *n);
int				p_step(t_psolver *g, t_pnode *n);
t_pnode			*p_findeq(t_psolver *g, t_stack *st);

t_array			p_solution(t_psolver *g);
const char		*op_name(t_op op);

void			p_setup(t_psolver *g);
void			p_free(t_psolver *g);
t_array			p_do_solve(t_stack *st, t_stack *sorted);
t_array			p_optimize(t_array ops, t_stack *st, t_stack *sorted);

#endif
