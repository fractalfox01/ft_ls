/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 16:58:20 by tvandivi          #+#    #+#             */
/*   Updated: 2020/02/04 15:19:25 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	ls_free_all(t_ls *ls)
{
	t_stack	*tmp;

	tmp = NULL;
	if (ls)
	{
		while (ls->stack)
		{
			tmp = ls->stack->next;
			free(ls->stack);
			ls->stack = tmp;
		}
	}
}

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
	int		i;
	int		j;
	char	*tmp;
	char	*ret;

	i = ft_strlen(s1);
	j = ft_strlen(s2);
	if (ft_strcmp(s1, "/") != 0)
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
	if (ft_strcmp(obj->entry->d_name, ".") != 0)
	{
		return (1);
	}
	if (ft_strcmp(obj->entry->d_name, "..") != 0)
	{
		return (1);
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
	{
		if (opt->f_all)
		{
			obj->merger = s_stk_push(&obj->merger, obj->entry->d_name, \
				obj->ptr);
			obj->sort = stack_push(&obj->sort, obj->entry->d_name, obj->path2);
			ret = st.st_blocks;
			obj->sort_total++;
		}
	}
	else
	{
		obj->merger = s_stk_push(&obj->merger, obj->entry->d_name, obj->ptr);
		obj->sort = stack_push(&obj->sort, obj->entry->d_name, obj->path2);
		ret = st.st_blocks;
		obj->sort_total++;
	}
	return (ret);
}
