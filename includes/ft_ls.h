/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 20:28:33 by tvandivi          #+#    #+#             */
/*   Updated: 2020/01/04 14:42:29 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <fcntl.h>
# include <sys/stat.h>
# include <strings.h>
# include <stdlib.h>
# include <stdio.h>
# include <time.h>
# include <sys/types.h>
# include <pwd.h>
# include <uuid/uuid.h>
# include <grp.h>
# include <sys/xattr.h>
# include <dirent.h>
# include "libft.h"

# define OPTION '-'
# define DEBUG	0
# define LSDIR	16877
# define LSFILE	33261

typedef	struct	s_ft_ls
{
	int				total;
	DIR				*dr;
	struct dirent	*dent;
	struct stat		st;
	struct passwd	*pw;
	struct group	*gr;
	t_list			*lookup;
	char			*output;
}				t_ls;

typedef struct	s_opt
{
	int			set;
	int			f_all;
	int			f_recurs;
	int			f_time;
	int			f_reverse;
	int			f_long;
}				t_opt;

int		is_option(char *str);
void	verify_options(int ac, char **av);
void    set_options(t_opt *opt, int ac, char **av);
void	init_ls(t_ls *ls, int total);
void	init_options(t_opt *opt);
void    verify_arguments(t_ls *ls, char **av, int ac);
void    set_arguments(t_ls *ls, t_opt *opt, char **av, int ac);

#endif
