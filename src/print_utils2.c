/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 15:21:08 by tvandivi          #+#    #+#             */
/*   Updated: 2020/02/06 13:55:44 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	print_ls_attr(t_ls_info *info)
{
	if (info->attr[0])
	{
		ft_putstr(info->attr);
		ft_putchar(' ');
	}
	else
		ft_putstr("  ");
}

void	print_ls_minor_major(t_ls_info *info, t_ls_pad *pad)
{
	if (info->file_mode[0] == 'c' || info->file_mode[0] == 'b')
	{
		print_ls_pad((pad->major_pad - (int)(ft_strlen(info->major))));
		ft_putstr(info->major);
		ft_putchar(',');
		print_ls_pad((pad->minor_pad - (int)(ft_strlen(info->minor))));
		ft_putstr(info->minor);
	}
	else
	{
		if (pad->major_pad > 0)
		{
			print_ls_pad(pad->major_pad + 1);
		}
		print_ls_pad(pad->bytes_pad - longlen(info->num_of_bytes) - 1);
		ft_putnbr(info->num_of_bytes);
	}
}

void	print_ls_accessed(t_ls_info *info)
{
	if (ft_strlen(info->dotm) == 1)
		ft_putchar(' ');
	ft_putchar(' ');
	ft_putstr(info->dotm);
	if (ft_strlen(info->hour_last) == 4)
		ft_putchar(' ');
}

void	print_long_format(t_ls_info *info, t_ls_pad *pad)
{
	ft_putstr(info->file_mode);
	print_ls_attr(info);
	print_ls_pad(pad->links_pad - ft_numlen(info->num_of_links));
	ft_putnbr(info->num_of_links);
	ft_putchar(' ');
	ft_putstr(info->owner);
	print_ls_pad((pad->owner_pad - (int)(ft_strlen(info->owner) - 1)));
	ft_putchar(' ');
	ft_putstr(info->group);
	ft_putchar(' ');
	print_ls_pad((pad->group_pad - (int)(ft_strlen(info->group) - 1)));
	print_ls_minor_major(info, pad);
	ft_putchar(' ');
	ft_putstr(info->month);
	print_ls_accessed(info);
	ft_putchar(' ');
	ft_putstr(info->hour_last);
	ft_putchar(' ');
}

void	print_ls_pad(int size)
{
	char	*tmp;

	if (size < 0)
		return ;
	tmp = get_padded(size);
	ft_putstr(tmp);
	ft_strdel(&tmp);
}
