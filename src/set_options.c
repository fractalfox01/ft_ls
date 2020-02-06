/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_options.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 16:01:13 by tvandivi          #+#    #+#             */
/*   Updated: 2020/02/05 14:41:45 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	ls_mark_option(t_opt *opt, char **av, int i, int j)
{
	if (av[i][j] == 'a')
		opt->f_all = 1;
	else if (av[i][j] == 'l')
		opt->f_long = 1;
	else if (av[i][j] == 'r')
		opt->f_reverse = 1;
	else if (av[i][j] == 't')
	{
		opt->f_time = 1;
	}
	else if (av[i][j] == 'R')
		opt->f_recurs = 1;
	else if (av[i][j] == 'c')
	{
		opt->f_ctime = 1;
	}
	else if (av[i][j] == 'A')
		opt->f_cap_a = 1;
}

void	set_options(t_opt *opt, int ac, char **av)
{
	int	i;
	int	j;

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
					ls_mark_option(opt, av, i, j++);
				j = 0;
			}
			else
				break ;
			i++;
		}
	}
}
