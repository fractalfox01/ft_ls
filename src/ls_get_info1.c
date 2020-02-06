/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_get_info1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 19:23:19 by tvandivi          #+#    #+#             */
/*   Updated: 2020/02/06 13:55:05 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	sp_helper1(char *name, t_ls_info *info)
{
	struct stat	st;

	lstat(name, &st);
	if (st.st_mode & S_IRUSR)
		info->file_mode[1] = 'r';
	if (st.st_mode & S_IWUSR)
		info->file_mode[2] = 'w';
	if (st.st_mode & S_IXUSR)
		info->file_mode[3] = 'x';
	if (st.st_mode & S_ISUID)
		info->file_mode[3] = 's';
	if (st.st_mode & S_IRGRP)
		info->file_mode[4] = 'r';
	if (st.st_mode & S_IWGRP)
		info->file_mode[5] = 'w';
	if (st.st_mode & S_IXGRP)
		info->file_mode[6] = 'x';
}

void	sp_helper2(char *name, t_ls_info *info)
{
	struct stat	st;

	lstat(name, &st);
	if (st.st_mode & S_ISGID)
		info->file_mode[6] = 's';
	if (st.st_mode & S_IROTH)
		info->file_mode[7] = 'r';
	if (st.st_mode & S_IWOTH)
		info->file_mode[8] = 'w';
	if (st.st_mode & S_IXOTH)
		info->file_mode[9] = 'x';
	if (st.st_mode & S_ISVTX)
		info->file_mode[9] = 't';
}

void	set_permissions(t_ls_info *info, char *name)
{
	sp_helper1(name, info);
	sp_helper2(name, info);
}

void	set_major_minor(t_ls_info *info, char *name)
{
	struct stat	st;
	char		*tmp;

	lstat(name, &st);
	if (S_ISCHR(st.st_mode) || S_ISBLK(st.st_mode))
	{
		tmp = ft_itoa(((int32_t)(((u_int32_t)(st.st_rdev) >> 24) & 0xff)));
		ft_memcpy(info->major, tmp, ft_strlen(tmp));
		ft_strdel(&tmp);
		tmp = ft_itoa(((int32_t)((st.st_rdev) & 0xffffff)));
		ft_memcpy(info->minor, tmp, ft_strlen(tmp));
		ft_strdel(&tmp);
	}
}
