/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 20:28:33 by tvandivi          #+#    #+#             */
/*   Updated: 2020/01/15 13:40:02 by tvandivi         ###   ########.fr       */
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

# define OPTION '0'
# define DEBUG	0
# define LSDIR	16877
# define LSFILE	33261


/*
** s_ls_obj and s_stack are used to store directories of the
** associated open directory name with most variables needed 
** carried along in s_ls_obj. used while recursing
** through directories.
*/
typedef struct      s_stack
{
    char            *name;
    struct s_stack  *next;
}                   t_stack;

/*
** The following structures s_ls_d and s_ms are used
** by the sorting functions in a merge sort implementation.
*/

typedef	struct		s_ls_d
{
	char			*name;
	int				pad_size;
	struct stat		st;
	struct passwd	*pw;
    struct group	*gr;
	struct s_ls_d	*next;
}					t_lst;

typedef struct      s_ls_obj
{
	int				sort_total;
	char			**table;
    t_stack         *dirs;
	t_stack			*sort;
    char            *tmp;
    DIR             *dir;
    struct dirent   *entry;
    struct stat     st;
    int             i;
    char            path2[1024];
    char            *ptr;
	t_lst			*merger;
}                   t_obj;

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
	t_stack		*sort_table;
}				t_ls;

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

/*
** Sorting prototypes
*/

t_lst	*get_node(t_lst *root, char *name);
void    ms_init(t_ms *ms, int i, int j);
void	copy_tab(t_ms *ms, int l, int m, char **tab);
void	readin_table(t_ms *ms, char **tab, int l, int m);
void	read_remaing(t_ms *ms, char **tab);
void	sort_by_character(t_ms *ms, char **tab);
void    sort_merge(t_obj *ls, int l, int r, void (*f)(t_obj *ls, int i, int j, int k));
void    s_merge_forward(t_obj *lst, int l, int m, int r);

int		stack_empty(t_stack *stack);
t_stack	*stack_push(t_stack **stack, char *name);
char	*stack_pop(t_stack **stack);
int		s_stk_empty(t_lst *stack);
t_lst	*s_stk_push(t_lst **stack, char *name);
char	*s_stk_pop(t_lst **stack);

int		is_option(char *str);
void	verify_options(int ac, char **av);
void    set_options(t_opt *opt, int ac, char **av);
void	init_ls(t_ls *ls, int total);
void	init_options(t_opt *opt);
t_stack	*verify_arguments(char **av, int ac);
void    set_arguments(t_ls *ls, t_opt *opt, char **av, int ac);

void	ls_free_all(t_ls *ls);

#endif
