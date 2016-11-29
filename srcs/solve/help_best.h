/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_best.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/27 23:13:10 by kyork             #+#    #+#             */
/*   Updated: 2016/11/28 15:25:25 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HELP_BEST_H
# define HELP_BEST_H

# include "../ps_stack.h"

/*
** This algorithm is largely based on this answer:
** http://codegolf.stackexchange.com/a/27036/7858
** We use rolling A as the first aux stack, and pushing B as the second aux
** stack.
*/

typedef struct	s_hsolver {
	ssize_t		hrollidx;
	ssize_t		hpushidx;

	t_stack		*st;
}				t_hsolver;

# define H_MAIN 0
# define H_ROLL 1
# define H_PUSH 2

ssize_t			h_getcount(t_hsolver *g, int which);
int				h_getel(t_hsolver *g, int which, ssize_t idx);

/*
** calling _start is setting everything=False
*/

void			h_main_to_help_best_start(t_hsolver *g,
					int dst, int helper, size_t offset);
void			h_main_to_help_best(t_hsolver *g,
					int dst, int helper, size_t offset);

void			h_move(t_hsolver *g, int src, int dst);
void			h_push_to_main(t_hsolver *g, int src, int count);
void			h_push_to_help(t_hsolver *g, int src, int dst, int count);
void			h_help_to_help(t_hsolver *g, int src, int dst, int count);
void			h_move_to_main(t_hsolver *g, int src, int help, int count);

t_array			help_sort(t_stack *st, t_stack *sorted);

#endif
