/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_stack_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 18:46:08 by tvandivi          #+#    #+#             */
/*   Updated: 2020/01/13 18:46:41 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int         stack_empty(t_stack *stack)
{
    if (stack)
    {
        if (stack->name)
            return (0);
    }
    return (1);
}

t_stack    *stack_push(t_stack **stack, char *name)
{
    t_stack *tmp;

    if (stack_empty(*stack) == 0)
    {
        tmp = (t_stack *)malloc(sizeof(t_stack) * 1);
        tmp->name = ft_strdup(name);
        tmp->next = *stack;
        return (tmp);
    }
    tmp = (t_stack *)malloc(sizeof(t_stack) * 1);
    tmp->name = ft_strdup(name);
    tmp->next = NULL;
    return (tmp);
}

char     *stack_pop(t_stack **stack)
{
    t_stack *tmp;
    char    *ret;

    ret = NULL;
    tmp = NULL;
    if (*stack)
    {
        
        tmp = *stack;
        ret = ft_strdup(tmp->name);
        stack[0] = stack[0]->next;
        ft_strdel(&(tmp->name));
        free(tmp);
        return (ret);
    }
    return (NULL);
}
