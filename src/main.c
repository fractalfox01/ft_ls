/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/31 10:37:04 by tvandivi          #+#    #+#             */
/*   Updated: 2020/02/06 12:11:54 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	sort_dir(t_obj *obj)
{
	int		i;
	int		j;
	t_stack	*tmp;
	t_obj	ls;

	i = 0;
	j = 0;
	tmp = obj->dirs;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	tmp = obj->dirs;
	ls.table = (char **)malloc(sizeof(char *) * (i + 1));
	while (j < i)
	{
		ls.table[j++] = ft_strdup(tmp->name);
		tmp = tmp->next;
	}
	sort_merge(&ls, 0, (j - 1), s_merge_forward);
}

void	ls_precheck(t_obj *obj, char *name, t_opt *opt, int *flag)
{
	t_ls_pad	pad;

	get_padding(&pad, obj, name, opt);
	if (!(obj->dir = opendir(name)))
	{
		if (opt->flag || flag[0])
			ft_putchar('\n');
		ft_putstr(name);
		ft_putstr(":\n");
		ft_putstr("ft_ls: ");
		ft_putstr(name);
		ft_putstr(" permission denied.\n");
		flag[0]++;
		return ;
	}
	if (opt->flag || flag[0])
		ft_putchar('\n');
	if ((*flag || opt->start > 1) || opt->done)
	{
		ft_putstr(name);
		ft_putstr(":\n");
	}
	flag[0]++;
}

void	fill_recursive(t_lsdir *ls, t_opt *opt)
{
	ls->inner.table = (char **)malloc(sizeof(char *) * (ls->obj.dir_total + 1));
	ls->tmp = ls->obj.dirs;
	ls->x = ls->obj.dir_total;
	while (--ls->x >= 0)
	{
		ls->inner.table[ls->x] = ft_strdup(ls->tmp->name);
		ls->inner.merger = s_stk_push(&ls->inner.merger, ls->tmp->name, \
			ls->tmp->name);
		ls->tmp = ls->tmp->next;
	}
	sort_by_option(&ls->obj, opt);
	ls->x = 0;
	while (ls->x < ls->obj.dir_total)
	{
		listdir(opt, ls->inner.table[ls->x]);
		ft_strdel(&(ls->inner.table[ls->x]));
		ls->x++;
	}
}

void	listdir(t_opt *opt, char *name)
{
	t_lsdir		ls;
	static int	flag;

	ls_init(&ls, &flag, name, opt);
	if (opt->f_recurs)
		fill_recursive(&ls, opt);
	clean_up(&ls.obj, &ls.inner);
}

int		main(int ac, char **av)
{
	t_stack	*tmp;
	t_opt	opt;
	char	*str;
	int		i;

	main_init(&i, &str, &tmp);
	init_options(&opt);
	verify_options(ac, av);
	set_options(&opt, ac, av);
	tmp = verify_arguments(av, ac, &opt);
	if ((ac == 1 || (ac == 2 && opt.set)) || ((opt.done == 0) && !tmp))
		listdir(&opt, ".");
	else if (ac >= 2)
	{
		if (opt.set)
			i++;
		while (is_option(av[i]))
			i++;
		while ((str = stack_pop(&tmp)))
		{
			listdir(&opt, str);
			ft_strdel(&str);
		}
	}
	return (0);
}
