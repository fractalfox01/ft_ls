/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 15:21:13 by tvandivi          #+#    #+#             */
/*   Updated: 2020/02/04 16:12:40 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	print_failure(t_ls_info *info, char *path2, char *name)
{
	int	i;

	i = 4;
	while (i < 10)
	{
		if (info->file_mode[i] == '-')
			i++;
		else
			break ;
	}
	if (i == 10)
	{
		ft_putstr("ft_ls: ");
		ft_putstr(name);
		ft_putstr(": permission denied\n");
	}
	else
	{
		ft_putstr("ft_ls: ");
		ft_putstr(path2);
		ft_putstr(": not a directory\n");
	}
}

void	print_single(char *path2, t_opt *opt, char *name, t_ls_pad *pad)
{
	t_ls_info	info;

	if (init_info(&info, path2) && pad)
	{
		if (opt->f_long)
			print_long_format(&info, pad);
		ft_putstr(name);
		if (info.symbolic[0] && opt->f_long)
		{
			ft_putstr(" -> ");
			ft_putstr(info.symbolic);
			ft_putchar('\n');
		}
		else
			ft_putchar('\n');
	}
	else
		print_failure(&info, path2, name);
	free_info(&info);
}

void	print_stack(t_obj *obj, t_opt *opt, char *name)
{
	t_ls_pad	pad;

	obj->dir_total = 0;
	sort_by_option(obj, opt);
	get_padding(&pad, obj, name);
	obj->x = 0;
	while (obj->x < obj->sort_total)
	{
		p_stack_do(obj, opt, name, &pad);
	}
	free(obj->table);
	obj->table = NULL;
}

void	print_total(long total)
{
	char	*t;

	t = ft_itoa(total);
	ft_putstr("total");
	ft_putchar(' ');
	ft_putstr(t);
	ft_putchar('\n');
	ft_strdel(&t);
}

void	save_and_print(t_opt *opt, t_obj *obj, char *name)
{
	long	total;
	int		count;

	total = 0;
	count = 0;
	if (obj->dir)
	{
		while ((obj->entry = readdir(obj->dir)) != NULL)
		{
			if (is_cur_or_prev(obj))
				count++;
			total += save_all(opt, obj, name);
		}
		if (opt->f_long && (count > 0 || opt->f_all))
			print_total(total);
		closedir(obj->dir);
	}
	save_table(obj);
	print_stack(obj, opt, name);
}
