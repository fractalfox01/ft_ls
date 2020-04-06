/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 20:28:33 by tvandivi          #+#    #+#             */
/*   Updated: 2020/02/06 14:01:34 by tvandivi         ###   ########.fr       */
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
# include <unistd.h>
# include "libft.h"

# define OPTION '-'
# define DEBUG	0

# define st_atime		     st_atim.tv_sec
# define st_mtime		     st_mtim.tv_sec
# define st_ctime		     st_ctim.tv_sec
# ifdef _POSIX_SOURCE
#  define st_birthtime	     st_birthtim.tv_sec
# endif

# ifdef _POSIX_SOURCE
#  define st_atimespec	     st_atim
#  define st_mtimespec	     st_mtim
#  define st_ctimespec	     st_ctim
#  define st_birthtimespec	     st_birthtim
# endif

/*
** s_ls_obj and s_stack are used to store directories of the
** associated open directory name with most variables needed
** carried along in s_ls_obj. used while recursing
** through directories.
*/

typedef struct		s_stack
{
	char			*full_path;
	char			*name;
	struct s_stack	*next;
}					t_stack;

/*
** The following structures s_ls_d and s_ms are used
** by the sorting functions in a merge sort implementation.
*/

typedef struct		s_ls_pad
{
	int				links_pad;
	int				owner_pad;
	int				group_pad;
	int				major_pad;
	int				minor_pad;
	int				bytes_pad;
	int				name_pad;
	int				i;
}					t_ls_pad;

typedef	struct		s_ls_d
{
	char			*name;
	t_ls_pad		pad;
	struct stat		st;
	struct passwd	*pw;
	struct group	*gr;
	struct s_ls_d	*next;
}					t_lst;

typedef struct		s_out_info
{
	char			dotm[3];
	char			month[4];
	char			hour_last[6];
	char			file_mode[11];
	char			major[15];
	char			minor[15];
	char			owner[33];
	char			group[33];
	char			name[1024];
	char			symbolic[1024];
	char			attr[2];
	int				num_of_links;
	long			num_of_bytes;
	long			nsec;
	time_t			sec;
}					t_ls_info;

typedef struct		s_ls_obj
{
	int				sort_total;
	int				dir_total;
	char			**table;
	char			**dir_tab;
	t_stack			*dirs;
	t_stack			*sort;
	char			*tmp;
	DIR				*dir;
	struct dirent	*entry;
	struct stat		st;
	int				i;
	int				x;
	char			path2[1024];
	char			*ptr;
	t_lst			*merger;
}					t_obj;

typedef struct		s_mini_obj
{
	int				sort_total;
	char			**table;
	t_lst			*merger;
	int				i;
	int				x;
}					t_mini_obj;

typedef struct		s_obj_table
{
	t_mini_obj		mn;
	t_mini_obj		obj;
	t_mini_obj		bad_param;
	int				i;
}					t_obj_tab;

/*
** The following sturcture s_ft_ls is used globaly throughout
** the programs lifetime.
** It carries a main list "lookup" that hold the names of
** files and directories to be printed to stdout.
*/

typedef	struct		s_ft_ls
{
	int				total;
	int				ls_args;
	t_stack			*stack;
	t_stack			*sort_table;
}					t_ls;

typedef struct		s_ms
{
	t_lst			*l1;
	t_lst			*l2;
	char			**left;
	char			**right;
	int				i;
	int				j;
	int				k;
	int				n1;
	int				n2;
	time_t			*t1;
	time_t			*t2;
	long			*t3;
	long			*t4;
}					t_ms;

/*
** The following structure s_opt is used for maintaining
** options state through various parts of the program.
*/

typedef struct		s_opt
{
	int				done;
	int				start;
	int				flag;
	int				set;
	int				f_all;
	int				f_cap_a;
	int				f_recurs;
	int				f_time;
	int				f_reverse;
	int				f_long;
	int				f_ctime;
}					t_opt;

typedef struct		s_listdir
{
	int				x;
	t_obj			obj;
	t_obj			inner;
	t_stack			*tmp;
}					t_lsdir;

/*
** Sorting prototypes
*/

t_lst				*get_node(t_lst *root, char *name);
void				ms_init(t_ms *ms, int i, int j);
void				free_ms(t_ms *ms);
void				copy_tab(t_ms *ms, int l, int m, char **tab);
void				readin_table(t_ms *ms, char **tab, int l, int m);
void				read_remaing(t_ms *ms, char **tab);
void				tsr_helper(t_ms *ms, char **tab);
void				tsf_helper(t_ms *ms, char **tab);
void				sort_by_character(t_ms *ms, char **tab);
void				sort_merge(t_obj *ls, int l, int r, void (*f)(t_obj *ls, \
						int i, int j, int k));
void				s_merge_forward(t_obj *lst, int l, int m, int r);
void				s_merge_time_forward(t_obj *ls, int l, int m, int r);
void				sort_by_ctime_forward(t_obj *ls, t_ms *ms, char **tab);
void				sort_by_time_forward(t_obj *ls, t_ms *ms, char **tab);
void				s_merge_ctime_forward(t_obj *ls, int l, int m, int r);
void				ls_sort_it(t_ms *ms, char **tab);
void				s_merge_reverse(t_obj *ls, int l, int m, int r);
void				s_merge_time_reverse(t_obj *ls, int l, int m, int r);
void				sort_by_time_reverse(t_obj *ls, t_ms *ms, char **tab);
void				sort_by_ctime_reverse(t_obj *ls, t_ms *ms, char **tab);
void				s_merge_ctime_reverse(t_obj *ls, int l, int m, int r);

void				p_stack_do(t_obj *obj, t_opt *opt, char *name, t_ls_pad \
						*pad);
int					stack_empty(t_stack *stack);
t_stack				*stack_push(t_stack **stack, char *name, char *full_path);
char				*stack_pop(t_stack **stack);
int					s_stk_empty(t_lst *stack);
t_lst				*s_stk_push(t_lst **stack, char *name, char *path);
t_lst				*s_stk_push_end(t_lst **stack, char *name, char *path);
char				*s_stk_pop(t_lst **stack);

void				print_single(char *path2, t_opt *opt, char *name, t_ls_pad \
						*pad);
void				print_ls_pad(int size);
void				print_ls_attr(t_ls_info *info);
void				print_long_format(t_ls_info *info, t_ls_pad *pad);

void				sort_by_option(t_obj *obj, t_opt *opt);
void				sort_by_option_mini(t_mini_obj *obj, t_opt *opt);
int					is_option(char *str);
void				verify_options(int ac, char **av);
void				set_options(t_opt *opt, int ac, char **av);
void				set_arguments(t_ls *ls, t_opt *opt, char **av, int ac);
t_stack				*verify_arguments(char **av, int ac, t_opt *opt);

void				free_info(t_ls_info *info);
long				save_all(t_opt *opt, t_obj *obj, char *name);
void				save_table(t_obj *obj);
void				ls_precheck(t_obj *obj, char *name, t_opt *opt, int *flag);
int					file_check(char	*name, t_mini_obj *bp);
int					dir_check(char *name, t_mini_obj *obj, t_opt *opt);
void				type_decider(char **av, t_obj_tab *obj_tab, t_opt *opt);
t_stack				*valid_directory(t_mini_obj *obj, t_opt *opt);
void				valid_file(t_mini_obj *obj, t_opt *opt);
void				bad_parameter(t_mini_obj *obj, t_opt *opt);

/*
** basic ls utilities
*/

void				ls_free_all(t_ls *ls);
int					is_directory(char *name);
char				*join_path(char *s1, char *s2);
int					is_cur_or_prev(t_obj *obj);
long				ls_if_hidden(t_obj *obj, t_opt *opt);

/*
** long output padding prototypes
*/

char				*get_padded(int size);
int					longlen(long num);
void				ls_set_pad(int itab[7], t_ls_pad *pad);
void				ls_do_pad(char *name, t_obj *obj, t_ls_pad *pad, t_opt *opt);
void				get_padding(t_ls_pad *pad, t_obj *obj, char *name, t_opt *opt);
void				ls_do_mini_pad(char *name, t_mini_obj *obj, t_ls_pad \
						*pad, t_opt *opt);
void				get_padding_mini(t_ls_pad *pad, t_mini_obj *obj, char \
						*name, t_opt *opt);

/*
** Prototypes for ls_get_info# functions
*/

void				set_group_and_password(t_ls_info *info, char *name);
void				get_attr(t_ls_info *info, char *name);
int					get_current_year(char *name, t_opt *opt);
void				set_time(t_ls_info *info, char *name, t_opt *opt);
int					month_and_time_helper(char *name, char ***tab, char **date, t_opt *opt);
void				set_month_and_time(t_ls_info *info, char *name, t_opt *opt);
long				get_major(int x);
long				get_minor(int x);
void				set_type(t_ls_info *info, char *name);
void				set_permissions(t_ls_info *info, char *name);
void				set_major_minor(t_ls_info *info, char *name);

/*
** Prototypes for init_utils.c
*/

void				ls_itab_init(int itab[7], t_ls_info *info);
void				free_info(t_ls_info *info);
long				save_all(t_opt *opt, t_obj *obj, char *name);
void				save_table(t_obj *obj);
void				ls_pad_init(t_ls_pad *pad);
void				free_obj(t_obj *obj);
void				clean_up(t_obj *p1, t_obj *p2);
void				ls_init(t_lsdir *ls, int *flag, char *name, t_opt *opt);
void				main_init(int *i, char **str, t_stack **tmp);
void				init_ls(t_ls *ls, int total);
void				init_options(t_opt *opt);
int					init_info(t_ls_info *info, char *name, t_opt *opt);
void				init_obj(t_obj *obj);

/*
** Prototypes for print_utils.c
*/

void				print_stack(t_obj *obj, t_opt *opt, char *name);
void				save_and_print(t_opt *opt, t_obj *obj, char *name);
void				listdir(t_opt *opt, char *name);

#endif
