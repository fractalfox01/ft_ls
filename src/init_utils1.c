/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 19:54:22 by tvandivi          #+#    #+#             */
/*   Updated: 2020/02/03 19:54:24 by tvandivi         ###   ########.fr       */
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
	opt->done = 0;
	opt->start = 0;
	opt->flag = 0;
	opt->f_all = 0;
	opt->f_long = 0;
	opt->f_recurs = 0;
	opt->f_reverse = 0;
	opt->f_time = 0;
	opt->set = 0;
}

void	init_obj(t_obj *obj)
{
	obj->sort_total = 0;
	obj->dir_total = 0;
	obj->i = 0;
	obj->table = NULL;
	obj->dir_tab = NULL;
	obj->dir = NULL;
	obj->entry = NULL;
	obj->dirs = NULL;
	obj->sort = NULL;
	obj->tmp = NULL;
	obj->entry = NULL;
	ft_bzero(obj->path2, 1024);
	obj->ptr = NULL;
	obj->merger = NULL;
}

void	info_null(t_ls_info *info)
{
	ft_bzero(info->attr, 2);
	ft_bzero(info->dotm, 3);
	ft_bzero(info->month, 4);
	ft_bzero(info->hour_last, 6);
	ft_bzero(info->file_mode, 11);
	ft_bzero(info->major, 15);
	ft_bzero(info->minor, 15);
	ft_bzero(info->owner, 33);
	ft_bzero(info->group, 33);
	ft_bzero(info->name, 1024);
	ft_bzero(info->symbolic, 1024);
}

int		init_info(t_ls_info *info, char *name)
{
	struct stat		st;

	info_null(info);
	if (lstat(name, &st) >= 0)
	{
		ft_memcpy(info->name, name, ft_strlen(name));
		set_major_minor(info, name);
		set_time(info, name);
		set_type(info, name);
		get_attr(info, name);
		set_permissions(info, name);
		set_group_and_password(info, name);
		set_month_and_time(info, name);
		info->num_of_links = st.st_nlink;
		info->num_of_bytes = st.st_size;
		return (1);
	}
	return (0);
}
