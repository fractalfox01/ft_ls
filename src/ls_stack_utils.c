/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_stack_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 18:46:08 by tvandivi          #+#    #+#             */
/*   Updated: 2020/02/04 11:53:21 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int		stack_empty(t_stack *stack)
{
	if (stack)
	{
		if (stack->name)
			return (0);
	}
	return (1);
}

t_stack	*stack_push(t_stack **stack, char *name, char *full_name)
{
	t_stack	*tmp;

	if (stack_empty(*stack) == 0)
	{
		tmp = (t_stack *)malloc(sizeof(t_stack) * 1);
		tmp->name = ft_strdup(name);
		tmp->full_path = ft_strdup(full_name);
		tmp->next = *stack;
		return (tmp);
	}
	tmp = (t_stack *)malloc(sizeof(t_stack) * 1);
	tmp->name = ft_strdup(name);
	tmp->full_path = ft_strdup(full_name);
	tmp->next = NULL;
	return (tmp);
}

char	*stack_pop(t_stack **stack)
{
	t_stack	*tmp;
	char	*ret;

	ret = NULL;
	tmp = NULL;
	if (*stack)
	{
		tmp = *stack;
		ret = ft_strdup(tmp->name);
		stack[0] = stack[0]->next;
		ft_strdel(&(tmp->name));
		ft_strdel(&(tmp->full_path));
		free(tmp);
		return (ret);
	}
	return (NULL);
}

void	p_stack_do(t_obj *obj, t_opt *opt, char *name, t_ls_pad *pad)
{
	obj->ptr = join_path(name, obj->table[obj->x]);
	obj->i = ft_strlen(name) + ft_strlen(obj->table[obj->x]) + 1;
	ft_memcpy(obj->path2, obj->ptr, obj->i);
	ft_strdel(&obj->ptr);
	print_single(obj->path2, opt, obj->table[obj->x], pad);
	lstat(obj->path2, &(obj->st));
	if (obj->st.st_mode >= S_IFDIR && obj->st.st_mode < S_IFBLK)
	{
		if ((ft_strcmp(obj->table[obj->x], ".") != 0 && \
			ft_strcmp(obj->table[obj->x], "..") != 0))
		{
			if (opt->f_recurs)
			{
				obj->dirs = stack_push(&obj->dirs, obj->path2, obj->path2);
				obj->dir_total++;
			}
		}
	}
	obj->st.st_mode = 0;
	ft_bzero(obj->path2, 1024);
	ft_strdel(&(obj->table[obj->x]));
	obj->x++;
}
