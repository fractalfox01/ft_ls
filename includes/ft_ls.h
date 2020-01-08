/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 20:28:33 by tvandivi          #+#    #+#             */
/*   Updated: 2020/01/08 13:32:33 by tvandivi         ###   ########.fr       */
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

/*
** The following structures s_ls_d and s_ms are used
** by the sorting functions in a merge sort implementation.
*/

typedef struct		s_stack
{
	char			dir_name[255];
	struct s_stack	*next;
}					t_stack;

typedef	struct		s_ls_d
{
	char			*name;
	int				pad_size;
	struct stat		st;
	struct passwd	*pw;
    struct group	*gr;
	struct s_ls_d	*next;
}					t_lst;

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

/*
** The following sturcture s_ft_ls is used globaly throughout
** the programs lifetime.
** It carries a main list "lookup" that hold the names of 
** files and directories to be printed to stdout.
*/

typedef	struct	s_ft_ls
{
	int			total;
	int			ls_args;
	t_stack		*stack;
}				t_ls;

/*
** The following structure s_opt is used for maintaining
** options state through various parts of the program.
*/

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
void    verify_arguments(char **av, int ac);
void    set_arguments(t_ls *ls, t_opt *opt, char **av, int ac);

void	ls_free_all(t_ls *ls);

#endif
