/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_padding_utils1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 11:41:28 by tvandivi          #+#    #+#             */
/*   Updated: 2020/02/06 11:43:37 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

char	*get_padded(int size)
{
	char *tmp;

	tmp = ft_strnew((size_t)size);
	ft_memset(tmp, ' ', (size_t)size);
	return (tmp);
}

int		longlen(long num)
{
	int	i;

	i = 0;
	while (num > 9)
	{
		i++;
		num = num / 10;
	}
	return (i);
}

void	ls_set_pad(int itab[7], t_ls_pad *pad)
{
	if (pad->group_pad < itab[0])
		pad->group_pad = itab[0];
	if (pad->owner_pad < itab[1])
		pad->owner_pad = itab[1];
	if (pad->links_pad < itab[2])
		pad->links_pad = itab[2];
	if (pad->bytes_pad < itab[3])
		pad->bytes_pad = itab[3];
	if (pad->major_pad < itab[4])
		pad->major_pad = itab[4];
	if (pad->minor_pad < itab[5])
		pad->minor_pad = itab[5];
	if (pad->name_pad < itab[6])
		pad->name_pad = itab[6];
}

void	ls_do_pad(char *name, t_obj *obj, t_ls_pad *pad, t_opt *opt)
{
	char		*tmp;
	int			itab[7];
	t_ls_info	info;
	struct stat	st;

	tmp = join_path(name, obj->table[pad->i]);
	lstat(tmp, &st);
	init_info(&info, tmp, opt);
	ft_strdel(&tmp);
	ls_itab_init(itab, &info);
	ls_set_pad(itab, pad);
}
