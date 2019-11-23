/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 18:28:15 by tvandivi          #+#    #+#             */
/*   Updated: 2019/11/22 18:29:09 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void    ms_init(t_ms *ms, int i, int j)
{
    ms->i = -1;
    ms->j = -1;
    ms->n1 = i;
    ms->n2 = j;
	ms->k = 0;
	ms->left = (char **)malloc(sizeof(char *) * i);
	ms->right = (char **)malloc(sizeof(char *) * j);
}

void	copy_tab(t_ms *ms, int l, int m, char **tab)
{
	while (++ms->i < ms->n1)
        ms->left[ms->i] = ft_strdup(tab[(l + ms->i)]);
    while (++ms->j < ms->n2)
        ms->right[ms->j] = ft_strdup(tab[(m + 1 + ms->j)]);
    ms->i = 0;
    ms->j = 0;
    ms->k = l;
}

void	readin_table(t_ms *ms, char **tab, int l, int m)
{
	while (++ms->i < ms->n1)
        ms->left[ms->i] = ft_strdup(tab[(l + ms->i)]);
    while (++ms->j < ms->n2)
        ms->right[ms->j] = ft_strdup(tab[(m + 1 + ms->j)]);
    ms->i = 0;
    ms->j = 0;
    ms->k = l;
}

void	read_remaing(t_ms *ms, char **tab)
{
	while (ms->i < ms->n1)
	{
		ft_strdel(&tab[ms->k]);
        tab[ms->k++] = ft_strdup(ms->left[ms->i++]);
	}
	while (ms->j < ms->n2)
    {
		ft_strdel(&tab[ms->k]);
		tab[ms->k++] = ft_strdup(ms->right[ms->j++]);
	}
}