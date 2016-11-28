/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_stack.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/27 15:35:55 by kyork             #+#    #+#             */
/*   Updated: 2016/11/27 17:38:36 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PS_STACK_H
# define PS_STACK_H

# include <libft.h>

# define AGET(st, which, idx) *(int*)ft_ary_get(&(st)->st_ ## which , idx)

typedef enum	e_ops {
	OP_INVALID,
	OP_SA,
	OP_SB,
	OP_SS,

	OP_PA,
	OP_PB,

	OP_RA,
	OP_RB,
	OP_RR,
	OP_RRA,
	OP_RRB,
	OP_RRR,
}				t_op;

typedef struct	s_stack {
	t_array		st_a;
	t_array		st_b;
	t_array		ops;
}				t_stack;
/*
** The top of a stack is the LAST index
**
** st_a, st_b: t_array<int>
** ops: t_array<t_op>
*/

void			stack_do(t_stack *st, t_op op);
void			stack_undo(t_stack *st);
t_stack			*stack_clone(t_stack *st);
void			stack_free(t_stack *st);

void			print_stack(t_stack *st);

t_stack			*read_input(int argc, char **argv);

#endif
