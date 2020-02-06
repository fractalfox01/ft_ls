/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_get_info2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 19:23:33 by tvandivi          #+#    #+#             */
/*   Updated: 2020/02/06 13:55:13 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	set_type(t_ls_info *info, char *name)
{
	struct stat st;
	char		buf[1024];
	int			i;

	i = 0;
	while (i < 10)
		info->file_mode[i++] = '-';
	lstat(name, &st);
	if (S_ISDIR(st.st_mode))
		info->file_mode[0] = 'd';
	else if (S_ISBLK(st.st_mode))
		info->file_mode[0] = 'b';
	else if (S_ISCHR(st.st_mode))
		info->file_mode[0] = 'c';
	else if (S_ISFIFO(st.st_mode))
		info->file_mode[0] = 'p';
	else if (S_ISLNK(st.st_mode))
	{
		info->file_mode[0] = 'l';
		ft_bzero(buf, 1024);
		ft_bzero(info->symbolic, 1024);
		readlink(name, buf, 255);
		ft_memcpy(info->symbolic, buf, ft_strlen(buf));
		ft_bzero(buf, 255);
	}
}

void	set_time(t_ls_info *info, char *name, t_opt *opt)
{
	struct stat	st;

	lstat(name, &st);
	if (opt->f_ctime)
	{
		info->sec = st.st_ctimespec.tv_sec;
		info->nsec = st.st_ctimespec.tv_nsec;
	}
	else
	{
		info->sec = st.st_mtimespec.tv_sec;
		info->nsec = st.st_mtimespec.tv_nsec;
	}
}

/*
** month_and_time_helper function pulls the files last modified time
** in seconds and stores in 'date'
** It also takes the returned date string and splits its components
** into a 2d char array
*/

int		month_and_time_helper(char *name, char ***tab, char **date, t_opt *opt)
{
	struct stat	st;

	lstat(name, &st);
	if (opt->f_ctime)
		*date = ctime(&(st.st_ctimespec.tv_sec));
	else
		*date = ctime(&(st.st_mtimespec.tv_sec));
	*tab = ft_strsplit(*date, ' ');
	return (0);
}

void	set_month_and_time(t_ls_info *info, char *name, t_opt *opt)
{
	char	**tab;
	char	*date;
	int		x;

	x = month_and_time_helper(name, &tab, &date, opt);
	ft_bzero(info->month, 4);
	ft_bzero(info->dotm, 3);
	ft_bzero(info->hour_last, 6);
	ft_memcpy(info->month, tab[1], ft_strlen(tab[1]));
	ft_memcpy(info->dotm, tab[2], 2);
	if ((get_current_year(name, opt)))
		ft_memcpy(info->hour_last, tab[3], 5);
	else
	{
		ft_memcpy(info->hour_last, tab[4], 4);
	}
	while (tab[x])
		ft_strdel(&tab[x++]);
	free(tab);
}
