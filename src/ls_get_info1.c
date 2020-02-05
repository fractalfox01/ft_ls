/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_get_info1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 19:23:19 by tvandivi          #+#    #+#             */
/*   Updated: 2020/02/03 19:35:59 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

long	get_major(int x)
{
	return (((int32_t)(((u_int32_t)(x) >> 24) & 0xff)));
}

long	get_minor(int x)
{
	return (((int32_t)((x) & 0xffffff)));
}

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

void	set_permissions(t_ls_info *info, char *name)
{
	struct stat	st;

	lstat(name, &st);
	if (st.st_mode & S_IRUSR)
		info->file_mode[1] = 'r';
	if (st.st_mode & S_IWUSR)
		info->file_mode[2] = 'w';
	if (st.st_mode & S_IXUSR)
		info->file_mode[3] = 'x';
	if (st.st_mode & S_IRGRP)
		info->file_mode[4] = 'r';
	if (st.st_mode & S_IWGRP)
		info->file_mode[5] = 'w';
	if (st.st_mode & S_IXGRP)
		info->file_mode[6] = 'x';
	if (st.st_mode & S_IROTH)
		info->file_mode[7] = 'r';
	if (st.st_mode & S_IWOTH)
		info->file_mode[8] = 'w';
	if (st.st_mode & S_IXOTH)
		info->file_mode[9] = 'x';
	if (st.st_mode & S_ISVTX)
		info->file_mode[9] = 't';
}

void	set_major_minor(t_ls_info *info, char *name)
{
	struct stat	st;
	char		*tmp;

	lstat(name, &st);
	if (S_ISCHR(st.st_mode) || S_ISBLK(st.st_mode))
	{
		tmp = ft_itoa(get_major(st.st_rdev));
		ft_memcpy(info->major, tmp, ft_strlen(tmp));
		ft_strdel(&tmp);
		tmp = ft_itoa(get_minor(st.st_rdev));
		ft_memcpy(info->minor, tmp, ft_strlen(tmp));
		ft_strdel(&tmp);
	}
}
