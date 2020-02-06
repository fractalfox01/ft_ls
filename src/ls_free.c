/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 11:48:23 by tvandivi          #+#    #+#             */
/*   Updated: 2020/02/06 11:48:45 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	ls_free_all(t_ls *ls)
{
	t_stack	*tmp;

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
