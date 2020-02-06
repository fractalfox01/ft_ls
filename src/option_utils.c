/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 09:55:25 by tvandivi          #+#    #+#             */
/*   Updated: 2020/02/05 22:39:46 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int		alloff(t_opt *opt)
{
	if ((opt->f_time == 0) && (opt->f_long == 0))
		return (1);
	return (0);
}

int		is_option(char *str)
{
	if (str[0] == OPTION)
		return (1);
	return (0);
}

void	sort_by_option(t_obj *obj, t_opt *opt)
{
	if (opt->f_reverse && (opt->f_time == 0))
		sort_merge(obj, 0, (obj->sort_total - 1), s_merge_reverse);
	else if ((opt->f_reverse == 0) && (opt->f_time && (opt->f_ctime == 0)))
		sort_merge(obj, 0, (obj->sort_total - 1), s_merge_time_forward);
	else if ((opt->f_reverse == 0) && (opt->f_ctime && alloff(opt)))
		sort_merge(obj, 0, (obj->sort_total - 1), s_merge_forward);
	else if ((opt->f_reverse == 0) && ((opt->f_ctime) && (opt->f_time)))
		sort_merge(obj, 0, (obj->sort_total - 1), s_merge_ctime_forward);
	else if (opt->f_reverse && opt->f_time && (opt->f_ctime == 0))
		sort_merge(obj, 0, (obj->sort_total - 1), s_merge_time_reverse);
	else if (opt->f_reverse && opt->f_ctime)
		sort_merge(obj, 0, (obj->sort_total - 1), s_merge_ctime_reverse);
	else
		sort_merge(obj, 0, (obj->sort_total - 1), s_merge_forward);
}

void	sort_by_option_mini(t_mini_obj *obj, t_opt *opt)
{
	t_obj	tmp;

	tmp.sort_total = obj->sort_total;
	tmp.table = obj->table;
	tmp.merger = obj->merger;
	if (opt->f_reverse && (opt->f_time == 0))
		sort_merge(&tmp, 0, (obj->sort_total - 1), s_merge_reverse);
	else if ((opt->f_reverse == 0) && opt->f_time)
		sort_merge(&tmp, 0, (obj->sort_total - 1), s_merge_time_forward);
	else if ((opt->f_reverse == 0) && opt->f_ctime)
		sort_merge(&tmp, 0, (obj->sort_total - 1), s_merge_ctime_forward);
	else if (opt->f_reverse && opt->f_time)
		sort_merge(&tmp, 0, (obj->sort_total - 1), s_merge_time_reverse);
	else if (opt->f_reverse && opt->f_ctime)
		sort_merge(&tmp, 0, (obj->sort_total - 1), s_merge_ctime_reverse);
	else
		sort_merge(&tmp, 0, (obj->sort_total - 1), s_merge_forward);
}
