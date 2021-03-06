/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_get_info3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 19:26:01 by tvandivi          #+#    #+#             */
/*   Updated: 2020/02/06 12:20:02 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	group_and_passwd_helper(int id, t_ls_info *info)
{
	char	*tmp;

	tmp = ft_itoa(id);
	ft_memcpy(info->owner, tmp, ft_strlen(tmp));
	ft_strdel(&tmp);
}

void	set_group_and_password(t_ls_info *info, char *name)
{
	struct stat		st;
	struct passwd	*pw;
	struct group	*gr;

	ft_bzero(info->owner, 33);
	ft_bzero(info->group, 33);
	lstat(name, &st);
	pw = getpwuid(st.st_uid);
	gr = getgrgid(st.st_gid);
	if (pw)
		ft_memcpy(info->owner, pw->pw_name, ft_strlen(pw->pw_name));
	else
		group_and_passwd_helper(st.st_uid, info);
	if (gr)
		ft_memcpy(info->group, gr->gr_name, ft_strlen(gr->gr_name));
	else
		group_and_passwd_helper(st.st_gid, info);
}

void	get_attr(t_ls_info *info, char *name)
{
	char			namebuf[255];
	char			*tmp;

	tmp = NULL;
	ft_bzero(namebuf, 255);
	ft_bzero(info->attr, 2);
#ifdef _POSIX_SOURCE
  	if (info->symbolic[0])
	{
		tmp = join_path("/", info->symbolic);
		if ((listxattr(name, namebuf, 255)) > 0)
			ft_memcpy(info->attr, "@", 1);
		ft_strdel(&tmp);
	}
	else if ((listxattr(name, namebuf, 255)) > 0)
		ft_memcpy(info->attr, "@", 1);
#endif
#ifndef _POSIX_SOURCE
	if (info->symbolic[0])
	{
		tmp = join_path("/", info->symbolic);
		if ((listxattr(name, namebuf, 255, XATTR_NOFOLLOW)) > 0)
			ft_memcpy(info->attr, "@", 1);
		ft_strdel(&tmp);
	}
	else if ((listxattr(name, namebuf, 255, XATTR_SHOWCOMPRESSION)) > 0)
		ft_memcpy(info->attr, "@", 1);
#endif
}

/*
** get_current_year's one job in life, get the year from the current time.
** and compare it against the passed in year.
*/

int		get_current_year(char *name, t_opt *opt)
{
	struct stat	st;
	time_t		teatime;

	lstat(name, &st);
	teatime = time(NULL);
	if (opt->f_ctime)
	{
		if (st.st_ctimespec.tv_sec >= (teatime - (15763200)))
		{
			if (st.st_ctimespec.tv_sec < (teatime))
				return (1);
		}
	}
	else
	{
		if (st.st_mtimespec.tv_sec >= (teatime - (15763200)))
		{
			if (st.st_mtimespec.tv_sec < (teatime))
				return (1);
		}
	}
	return (0);
}
