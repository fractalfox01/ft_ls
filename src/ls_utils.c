/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 16:58:20 by tvandivi          #+#    #+#             */
/*   Updated: 2020/02/06 13:41:42 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int		is_directory(char *name)
{
	struct stat	st;

	lstat(name, &st);
	if (st.st_mode >= S_IFDIR && st.st_mode < S_IFBLK)
		return (1);
	return (0);
}

char	*join_path(char *s1, char *s2)
{
	char	*tmp;
	char	*ret;

	if ((ft_strcmp(s1, "/") != 0) && (ft_strcmp(s1, "") != 0))
	{
		tmp = ft_strjoin(s1, "/");
		ret = ft_strjoin(tmp, s2);
		ft_strdel(&tmp);
		return (ret);
	}
	ret = ft_strjoin(s1, s2);
	return (ret);
}

int		is_cur_or_prev(t_obj *obj)
{
	if (ft_strcmp(obj->entry->d_name, ".") == 0)
	{
		return (0);
	}
	if (ft_strcmp(obj->entry->d_name, "..") == 0)
	{
		return (0);
	}
	return (1);
}

long	check_push_all(t_opt *opt, t_obj *obj, struct stat *st)
{
	if (opt->f_all || opt->f_cap_a)
	{
		if (is_cur_or_prev(obj) && opt->f_cap_a)
		{
			obj->merger = s_stk_push(&obj->merger, obj->entry->d_name, \
				obj->ptr);
			obj->sort = stack_push(&obj->sort, obj->entry->d_name, obj->path2);
			obj->sort_total++;
			return (st->st_blocks);
		}
		if (opt->f_cap_a == 0)
		{
			obj->merger = s_stk_push(&obj->merger, obj->entry->d_name, \
				obj->ptr);
			obj->sort = stack_push(&obj->sort, obj->entry->d_name, obj->path2);
			obj->sort_total++;
			return (st->st_blocks);
		}
	}
	return (0);
}

long	ls_if_hidden(t_obj *obj, t_opt *opt)
{
	long		ret;
	struct stat	st;

	ret = 0;
	lstat(obj->ptr, &st);
	if (obj->entry->d_name[0] == '.')
		ret = check_push_all(opt, obj, &st);
	else
	{
		obj->merger = s_stk_push(&obj->merger, obj->entry->d_name, obj->ptr);
		obj->sort = stack_push(&obj->sort, obj->entry->d_name, obj->path2);
		ret = st.st_blocks;
		obj->sort_total++;
	}
	return (ret);
}
