/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_arguments.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 10:20:22 by tvandivi          #+#    #+#             */
/*   Updated: 2020/02/04 15:35:49 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static int		stack_exist(t_stack *stack)
{
	if (stack)
		return (1);
	return (0);
}

static t_stack	*stack_add(t_stack *stack, char *d_name)
{
	t_stack	*tmp;

	if (stack_exist(stack))
	{
		tmp = (t_stack *)malloc(sizeof(t_stack) * 1);
		tmp->next = stack;
		tmp->name = ft_strdup(d_name);
		return (tmp);
	}
	else
	{
		stack = (t_stack *)malloc(sizeof(t_stack) * 1);
		stack->name = ft_strdup(d_name);
	}
	return (stack);
}

void			ls_try_read(t_ls *ls)
{
	DIR				*dr;
	struct dirent	*dent;
	struct stat		st;

	dr = opendir(".");
	while ((dent = readdir(dr)))
	{
		if ((lstat(dent->d_name, &st)) == 0)
		{
			if (st.st_mode >= S_IFDIR && st.st_mode < S_IFBLK && \
				(ft_strcmp(dent->d_name, ".") != 0) && \
					(ft_strcmp(dent->d_name, "..") != 0))
			{
				ls->stack = stack_add(ls->stack, dent->d_name);
			}
		}
		dent = NULL;
	}
	closedir(dr);
}

void			ls_try_save(int ac, char **av, t_ls *ls, t_opt *opt)
{
	int				i;
	struct stat		st;

	i = 0;
	while (i < ac && opt)
	{
		if (av[i][0] != OPTION)
		{
			if ((lstat(av[i], &st)) == 0)
			{
				if (st.st_mode >= S_IFDIR && st.st_mode < S_IFBLK)
				{
					ls->stack = stack_add(ls->stack, av[i]);
					ls->ls_args += 1;
				}
				else
				{
					ft_putstr(av[i]);
					ft_putchar('\n');
				}
			}
			st.st_mode = 0;
		}
		i++;
	}
}

void			set_arguments(t_ls *ls, t_opt *opt, char **av, int ac)
{
	if (ac <= 2 && ((opt->set) || ac == 1))
		ls_try_read(ls);
	else
		ls_try_save(ac, av, ls, opt);
}
