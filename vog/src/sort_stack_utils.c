/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_stack_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 11:31:59 by tvandivi          #+#    #+#             */
/*   Updated: 2020/01/15 11:37:29 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int     s_stk_empty(t_lst *stack)
{
    if (stack)
    {
        if (stack->name)
            return (0);
    }
    return (1);
}

t_lst   *s_stk_push(t_lst **stack, char *name)
{
    t_lst *tmp;

    if (s_stk_empty(*stack) == 0)
    {
        tmp = (t_lst *)malloc(sizeof(t_lst) * 1);
        tmp->name = ft_strdup(name);
        lstat(name, &tmp->st);
        tmp->next = *stack;
        return (tmp);
    }
    tmp = (t_lst *)malloc(sizeof(t_lst) * 1);
    tmp->name = ft_strdup(name);
    lstat(name, &tmp->st);
    tmp->next = NULL;
    return (tmp);
}

char    *s_stk_pop(t_lst **stack)
{
    t_lst *tmp;
    char    *ret;

    ret = NULL;
    tmp = NULL;
    if (*stack)
    {
        
        tmp = *stack;
        ret = ft_strdup(tmp->name);
        stack[0] = stack[0]->next;
        ft_strdel(&(tmp->name));
        lstat(tmp->name, &tmp->st);
        free(tmp);
        return (ret);
    }
    return (NULL);
}