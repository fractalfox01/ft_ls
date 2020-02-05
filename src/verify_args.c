/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 10:18:55 by tvandivi          #+#    #+#             */
/*   Updated: 2020/02/04 14:48:01 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int		file_check(char *name, t_mini_obj *bp)
{
	struct stat	st;

	st.st_mode = 0;
	if (lstat(name, &st) < 0)
	{
		if (st.st_mode <= 0)
		{
			bp->merger = s_stk_push(&(bp->merger), name, name);
			bp->sort_total++;
			return (1);
		}
		return (1);
	}
	return (0);
}

int		dir_check(char *name, t_mini_obj *obj, t_opt *opt)
{
	struct stat	st;
	char		buf[256];

	lstat(name, &st);
	if (st.st_mode >= S_IFDIR && st.st_mode < S_IFBLK)
	{
		obj->sort_total++;
		obj->merger = s_stk_push(&(obj->merger), name, name);
		return (1);
	}
	else if ((opt->f_long == 0) && S_ISLNK(st.st_mode))
	{
		ft_bzero(buf, 256);
		readlink(name, buf, 255);
		obj->sort_total++;
		obj->merger = s_stk_push(&obj->merger, name, buf);
		ft_bzero(buf, 256);
		return (1);
	}
	return (0);
}

void	init_mini(t_mini_obj *obj)
{
	obj->sort_total = 0;
	obj->i = 0;
	obj->table = NULL;
	obj->merger = NULL;
}

void	init_verify_objects(t_obj_tab *obj_tab)
{
	init_mini(&(obj_tab->mn));
	init_mini(&(obj_tab->obj));
	init_mini(&(obj_tab->bad_param));
}

t_stack	*verify_arguments(char **av, int ac, t_opt *opt)
{
	t_obj_tab	obj_tab;

	init_verify_objects(&obj_tab);
	obj_tab.i = (ac);
	while (--obj_tab.i > 0)
		type_decider(av, &obj_tab, opt);
	if (obj_tab.bad_param.sort_total)
	{
		opt->done = 1;
		bad_parameter(&obj_tab.bad_param, opt);
	}
	if (obj_tab.obj.sort_total)
	{
		opt->done = 1;
		valid_file(&obj_tab.obj, opt);
	}
	if (obj_tab.mn.sort_total)
		return (valid_directory(&obj_tab.mn, opt));
	return (NULL);
}
