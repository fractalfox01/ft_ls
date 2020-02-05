/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_padding_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 11:47:01 by tvandivi          #+#    #+#             */
/*   Updated: 2020/02/04 11:48:45 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	get_padding(t_ls_pad *pad, t_obj *obj, char *name)
{
	int				i;

	ls_pad_init(pad, &i);
	while (i < obj->sort_total)
		ls_do_pad(name, obj, pad, i++);
}

void	ls_do_mini_pad(char *name, t_mini_obj *obj, t_ls_pad *pad, int i)
{
	char		*tmp;
	int			itab[7];
	t_ls_info	info;
	struct stat	st;

	tmp = join_path(name, obj->table[i]);
	lstat(tmp, &st);
	init_info(&info, tmp);
	ft_strdel(&tmp);
	ls_itab_init(itab, &info);
	ls_set_pad(itab, pad);
}

void	get_padding_mini(t_ls_pad *pad, t_mini_obj *obj, char *name)
{
	int				i;

	ls_pad_init(pad, &i);
	while (i < obj->sort_total)
		ls_do_mini_pad(name, obj, pad, i++);
}
