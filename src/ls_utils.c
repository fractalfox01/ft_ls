/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 16:58:20 by tvandivi          #+#    #+#             */
/*   Updated: 2020/01/08 11:24:05 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void    ls_free_all(t_ls *ls)
{
	t_stack *tmp;

	tmp = NULL;
    if (ls)
	{
		while (ls->stack)
		{
			tmp = ls->stack->next;
			free(ls->stack);
			ls->stack = tmp;
		}
	}
}