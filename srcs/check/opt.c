/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/29 14:22:56 by kyork             #+#    #+#             */
/*   Updated: 2016/12/29 14:25:16 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ps_check.h"

int			parse_opts(char **argv, int (*optf)(char))
{
	int		i;
	int		ac;
	int		opt_count;

	ac = 1;
	opt_count = 0;
	while (argv[ac])
		if (argv[ac][0] == '-')
		{
			if (argv[ac][1] == 0)
				break ;
			if (ft_atoi(argv[ac]) != 0)
				break ;
			opt_count++;
			i = 0;
			while (argv[ac][++i])
				if (-1 == optf(argv[ac][i]))
					return (-1);
			ac++;
		}
		else
			break ;
	return (opt_count);
}
