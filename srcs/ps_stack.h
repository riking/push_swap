/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_stack.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/27 15:35:55 by kyork             #+#    #+#             */
/*   Updated: 2016/11/27 23:41:01 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PS_STACK_H
# define PS_STACK_H

# include <libft.h>
# include <stdint.h>

# define AGET(st, which, idx) *(int*)ft_ary_get(&(st)->st_ ## which , idx)
# define RGET(ary, idx) *(int*)ft_ary_get(ary, idx)

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
	OP_STOPITER,
}				t_op;

# define OP_LAST OP_RRR

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

t_op			op_inverse(t_op op);

void			stack_do(t_stack *st, t_op op);
void			stack_undo(t_stack *st);

t_stack			*stack_clone(t_stack *st);
void			stack_free(t_stack *st);
int				stack_cmp(t_stack *s1, t_stack *s2);
uint32_t		stack_hash(t_stack *st);

uint32_t		mixhash(uint32_t hash);
void			print_stack(t_stack *st);

t_stack			*read_input(int argc, char **argv);

#endif
