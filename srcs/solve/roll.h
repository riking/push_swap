/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   roll.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 14:04:47 by kyork             #+#    #+#             */
/*   Updated: 2016/12/10 19:10:11 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROLL_H
# define ROLL_H

# include "../ps_stack.h"

typedef struct	s_rsolver {
	t_stack		*st;
	int			*swap_needs;
	ssize_t		size;
	int			rollidx;
}				t_rsolver;

t_array			roll_solve_b(t_stack *st, t_stack *sorted, int preroll);
t_array			roll_solve(t_stack *st, t_stack *sorted);

#endif
