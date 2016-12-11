/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_stack.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/27 15:35:55 by kyork             #+#    #+#             */
/*   Updated: 2016/12/10 17:20:26 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PS_STACK_H
# define PS_STACK_H

# include <libft.h>
# include <stdint.h>
# include <stdbool.h>

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

typedef bool	t_side;

# define ST_A (t_side)false
# define ST_B (t_side)true

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

/*
** op_inverse returns the operation needed to undo the given op
*/
t_op			op_inverse(t_op op);

/*
** op_on returns the parameter operation scoped to only the A or B stack
*/
t_op			op_on(t_op op, t_side whichstack);

/*
** stack_get returns the idx item of the whichstack stack
** if idx is negative, counts from the top
** if idx is positive, counts from the bottom
*/
int				stack_get(t_stack *st, t_side whichstack, int idx);

void			stack_do(t_stack *st, t_op op);
void			stack_undo(t_stack *st);

t_stack			*stack_clone(t_stack *st);
void			stack_free(t_stack *st);
int				stack_cmp(t_stack *s1, t_stack *s2);
uint32_t		stack_hash(t_stack *st);
bool			is_sorted(t_stack *st);

/*
** mixhash: mixes the bits of a hash so they are evenly spread
** print_stack: prints the stack to stderr
** cmp_int: for use with ft_ary_sort on stack arrays
*/
uint32_t		mixhash(uint32_t hash);
void			print_stack(t_stack *st);
int				cmp_int(void *left, void *right, size_t size, void *data);

t_stack			*read_input(int argc, char **argv);

#endif
