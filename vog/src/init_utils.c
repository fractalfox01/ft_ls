/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 16:29:03 by tvandivi          #+#    #+#             */
/*   Updated: 2020/01/08 13:34:47 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	init_ls(t_ls *ls, int total)
{
	ls->total = total;
	ls->stack = NULL;
	ls->ls_args = 0;
}

void	init_options(t_opt *opt)
{
	opt->f_all = 0;
	opt->f_long = 0;
	opt->f_recurs = 0;
	opt->f_reverse = 0;
	opt->f_time = 0;
	opt->set = 0;
}