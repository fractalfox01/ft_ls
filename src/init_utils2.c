/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 19:54:40 by tvandivi          #+#    #+#             */
/*   Updated: 2020/02/04 15:19:53 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	ls_init(t_lsdir *ls, int *flag, char *name, t_opt *opt)
{
	ls->x = 0;
	init_obj(&ls->obj);
	init_obj(&ls->inner);
	ls_precheck(&ls->obj, name, opt, flag);
	save_and_print(opt, &ls->obj, name);
	ls->obj.sort_total = 0;
}

void	main_init(int *i, char **str, t_stack **tmp)
{
	*i = 1;
	*str = NULL;
	*tmp = NULL;
}

void	clean_up(t_obj *p1, t_obj *p2)
{
	free_obj(p1);
	free_obj(p2);
}

void	free_obj(t_obj *obj)
{
	char	*str;

	str = NULL;
	if (obj->merger)
		while ((str = s_stk_pop(&obj->merger)))
			ft_strdel(&str);
	if (obj->sort)
		while ((str = stack_pop(&obj->sort)))
			ft_strdel(&str);
	if (obj->dirs)
		while ((str = stack_pop(&obj->dirs)))
			ft_strdel(&str);
	if (obj->table)
		free(obj->table);
}

void	ls_pad_init(t_ls_pad *pad, int *i)
{
	pad->name_pad = 0;
	pad->bytes_pad = 0;
	pad->group_pad = 0;
	pad->links_pad = 0;
	pad->major_pad = 0;
	pad->minor_pad = 0;
	pad->owner_pad = 0;
	i[0] = 0;
}
