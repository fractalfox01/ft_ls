/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 11:45:33 by tvandivi          #+#    #+#             */
/*   Updated: 2020/02/04 15:19:12 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	ls_itab_init(int itab[7], t_ls_info *info)
{
	itab[0] = (int)ft_strlen(info->group);
	itab[1] = (int)ft_strlen(info->owner);
	itab[2] = (int)ft_numlen(info->num_of_links);
	itab[3] = (int)ft_numlen(info->num_of_bytes);
	itab[4] = (int)ft_strlen(info->major);
	itab[5] = (int)ft_strlen(info->minor);
	itab[6] = (int)ft_strlen(info->name);
}

void	free_info(t_ls_info *info)
{
	if (info->file_mode[0])
	{
		info->num_of_links = 0;
		info->num_of_bytes = 0;
		info->nsec = 0;
		info->sec = 0;
		if (info->owner[0])
			ft_bzero(&info->owner, 33);
		if (info->group[0])
			ft_bzero(&info->group, 33);
		ft_bzero(&info->month, 4);
		ft_bzero(&info->hour_last, 6);
		ft_bzero(info->file_mode, 11);
		ft_bzero(info->major, 15);
		ft_bzero(info->minor, 15);
		ft_bzero(&info->name, 1024);
		ft_bzero(&info->dotm, 3);
		ft_bzero(&info->attr, 2);
		ft_bzero(&info->symbolic, 1024);
	}
}

long	save_all(t_opt *opt, t_obj *obj, char *name)
{
	long		ret;
	struct stat	st;

	ret = 0;
	obj->ptr = join_path(name, obj->entry->d_name);
	obj->i = ft_strlen(name) + ft_strlen(obj->entry->d_name) + 1;
	ft_memcpy(obj->path2, obj->ptr, obj->i);
	lstat(obj->ptr, &st);
	ret = ls_if_hidden(obj, opt);
	ft_strdel(&(obj->ptr));
	ft_bzero(obj->path2, 1024);
	obj->st.st_mode = 0;
	obj->i = 0;
	return (ret);
}

void	save_table(t_obj *obj)
{
	int		i;
	t_stack	*list;

	i = 0;
	list = obj->sort;
	obj->table = (char **)malloc(sizeof(char *) * (obj->sort_total + 1));
	while (i < obj->sort_total)
	{
		obj->table[i] = ft_strdup(list->name);
		list = list->next;
		i++;
	}
	obj->table[i] = NULL;
}
