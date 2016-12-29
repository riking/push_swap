/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_check.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/27 16:47:24 by kyork             #+#    #+#             */
/*   Updated: 2016/12/29 14:24:57 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PS_CHECK_H
# define PS_CHECK_H

# include "../ps_stack.h"

void		print_stack(t_stack *st);
t_op		parse_op(char *str);
int			parse_opts(char **argv, int (*optf)(char));

#endif
