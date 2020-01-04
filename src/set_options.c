/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_options.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 16:01:13 by tvandivi          #+#    #+#             */
/*   Updated: 2020/01/03 10:12:06 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void    set_options(t_opt *opt, int ac, char **av)
{
    int	i;
    int j;

	i = 1;
    j = 0;
	if (ac >= 2 && opt)
	{
		while (i < ac)
		{
			if (is_option(av[i]))
			{
                opt->set = 1;
				while (av[i][j] != '\0')
                {
                    if (av[i][j] == 'a')
                        opt->f_all = 1;
                    else if (av[i][j] == 'l')
                        opt->f_long = 1;
                    else if (av[i][j] == 'r')
                        opt->f_reverse = 1;
                    else if (av[i][j] == 't')
                        opt->f_time = 1;
                    else if (av[i][j] == 'R')
                        opt->f_recurs = 1;
                    j++;
                }
                j = 0;
			}
			else
				break ;
			i++;
		}
	}
    if (opt->set && DEBUG)
		ft_printf("all: %d\nlong: %d\nrecursive: %d\nreverse: %d\ntime: %d\n", opt->f_all, opt->f_long, opt->f_recurs, opt->f_reverse, opt->f_time);
}