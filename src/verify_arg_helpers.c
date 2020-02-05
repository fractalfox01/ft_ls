/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_arg_helpers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 19:39:58 by tvandivi          #+#    #+#             */
/*   Updated: 2020/02/04 15:42:43 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void		type_decider(char **av, t_obj_tab *obj_tab, t_opt *opt)
{
	if (av[obj_tab->i][0] != OPTION)
	{
		if (file_check(av[obj_tab->i], &obj_tab->bad_param) == 0)
		{
			if (dir_check(av[obj_tab->i], &obj_tab->mn, opt) == 0)
			{
				obj_tab->obj.merger = s_stk_push(&(obj_tab->obj.merger), \
					av[obj_tab->i], av[obj_tab->i]);
				obj_tab->obj.sort_total++;
			}
			else
				opt->start++;
		}
	}
}

/*
** The verify_arguments function verifies if the user passed arguments are
** valid (argument is a file or directory).
** If not, then the function prints an error to stdout and continues.
*/

t_stack		*valid_directory(t_mini_obj *obj, t_opt *opt)
{
	t_stack	*tmp;
	t_lst	*tptr;
	char	*str;

	obj->table = (char **)malloc(sizeof(char *) * (obj->sort_total + 1));
	tptr = obj->merger;
	tmp = NULL;
	while (obj->i < obj->sort_total)
	{
		obj->table[obj->i] = ft_strdup(tptr->name);
		tptr = tptr->next;
		obj->i++;
	}
	obj->table[obj->i] = NULL;
	sort_by_option_mini(obj, opt);
	while ((obj->i--) > 0)
		tmp = stack_push(&tmp, obj->table[(obj->i)], obj->table[(obj->i)]);
	while ((str = s_stk_pop(&obj->merger)))
		ft_strdel(&str);
	obj->i = 0;
	while (obj->i < obj->sort_total)
		ft_strdel(&obj->table[obj->i++]);
	free(obj->table);
	return (tmp);
}

void		valid_file(t_mini_obj *obj, t_opt *opt)
{
	t_lst		*tptr;
	char		*tmp;
	t_ls_pad	pad;

	obj->table = (char **)malloc(sizeof(char *) * (obj->sort_total + 1));
	tptr = obj->merger;
	while (obj->i < obj->sort_total)
	{
		obj->table[obj->i] = ft_strdup(tptr->name);
		tptr = tptr->next;
		obj->i++;
	}
	obj->table[obj->i] = NULL;
	sort_by_option_mini(obj, opt);
	get_padding_mini(&pad, obj, "");
	obj->i = -1;
	while (++obj->i < obj->sort_total)
	{
		print_single(obj->table[(obj->i)], opt, obj->table[(obj->i)], &pad);
		ft_strdel(&obj->table[obj->i]);
		opt->flag++;
	}
	free(obj->table);
	while ((tmp = s_stk_pop(&obj->merger)))
		ft_strdel(&tmp);
}

void		bad_parameter(t_mini_obj *obj, t_opt *opt)
{
	t_lst	*tptr;
	char	*str;

	str = NULL;
	obj->table = (char **)malloc(sizeof(char *) * (obj->sort_total + 1));
	tptr = obj->merger;
	while (obj->i < obj->sort_total)
	{
		obj->table[obj->i] = ft_strdup(tptr->name);
		tptr = tptr->next;
		obj->i++;
	}
	obj->table[obj->i] = NULL;
	sort_by_option_mini(obj, opt);
	obj->i = 0;
	while (obj->i < obj->sort_total)
	{
		ft_putstr("ft_ls: ");
		ft_putstr(obj->table[(obj->i)]);
		ft_putstr(": No such file or directory\n");
		ft_strdel(&obj->table[obj->i++]);
	}
	free(obj->table);
	while ((str = s_stk_pop(&obj->merger)))
		ft_strdel(&str);
}
