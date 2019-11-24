/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 20:28:33 by tvandivi          #+#    #+#             */
/*   Updated: 2019/11/23 10:33:24 by tvandivi         ###   ########.fr       */
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

# define LSDIR 16877
# define LSFILE 33261

typedef	struct		s_ls_d
{
	char			*name;
	int				pad_size;
	struct stat		st;
	struct passwd	*pw;
    struct group	*gr;
	struct s_ls_d	*next;
}					t_lst;


typedef struct	s_lslist
{
	int				total;
	uint64_t		t_links;
	char			flags[5];
	char			**sort_table;
	DIR				*ddir;
	struct dirent	*dent;
	int				pad_size;
	struct stat		st;
	struct passwd	*pw;
    struct group	*gr;
	t_lst			*lst;
}					t_ls;

typedef struct  s_ms
{
	t_lst		*l1;
	t_lst		*l2;
	char		**left;
	char		**right;
    int         i;
    int         j;
    int         k;
    int         n1;
    int         n2;
	time_t		*t1;
	time_t		*t2;
	time_t		*t3;
	time_t		*t4;
}               t_ms;

void	sort_list(t_ls *ls);
void	init_ls(t_ls *ls);

void	sort_by_character(t_ms *ms, char **tab);
void    s_merge_forward(t_ls *ls, int l, int m, int r);
void	time_sort_forward(t_ms *ms, char **tab);
void	sort_by_time_forward(t_ls *ls, t_ms *ms, char **tab);
void    s_merge_time_forward(t_ls *ls, int l, int m, int r);
void    s_merge_reverse(t_ls *ls, int l, int m, int r);
void	time_sort_reverse(t_ms *ms, char **tab);
void	sort_by_time_reverse(t_ls *ls, t_ms *ms, char **tab);
void    s_merge_time_reverse(t_ls *ls, int l, int m, int r);

void    ms_init(t_ms *ms, int i, int j);
void	copy_tab(t_ms *ms, int l, int m, char **tab);
void	readin_table(t_ms *ms, char **tab, int l, int m);
void	read_remaing(t_ms *ms, char **tab);
t_lst	*get_node(t_lst *root, char *name);

#endif
