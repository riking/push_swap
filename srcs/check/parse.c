/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/27 17:34:20 by kyork             #+#    #+#             */
/*   Updated: 2016/11/27 17:38:30 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ps_check.h"
#include <ft_guard.h>

t_op	parse_op(char *str)
{
	ZGUARD(GFAIL(OP_SA, 0), !ft_strcmp(str, "sa"));
	ZGUARD(GFAIL(OP_SB, 0), !ft_strcmp(str, "sb"));
	ZGUARD(GFAIL(OP_SS, 0), !ft_strcmp(str, "ss"));
	ZGUARD(GFAIL(OP_PA, 0), !ft_strcmp(str, "pa"));
	ZGUARD(GFAIL(OP_PB, 0), !ft_strcmp(str, "pb"));
	ZGUARD(GFAIL(OP_RA, 0), !ft_strcmp(str, "ra"));
	ZGUARD(GFAIL(OP_RB, 0), !ft_strcmp(str, "rb"));
	ZGUARD(GFAIL(OP_RR, 0), !ft_strcmp(str, "rr"));
	ZGUARD(GFAIL(OP_RRA, 0), !ft_strcmp(str, "rra"));
	ZGUARD(GFAIL(OP_RRB, 0), !ft_strcmp(str, "rrb"));
	ZGUARD(GFAIL(OP_RRR, 0), !ft_strcmp(str, "rrr"));
	return (OP_INVALID);
}
