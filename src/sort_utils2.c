/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 12:36:43 by tvandivi          #+#    #+#             */
/*   Updated: 2020/02/03 20:09:57 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

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

void	sort_by_character(t_ms *ms, char **tab)
{
	if (ft_strcmp(ms->left[ms->i], ms->right[ms->j]) <= 0)
	{
		ft_strdel(&tab[ms->k]);
		tab[ms->k] = ft_strdup(ms->left[ms->i++]);
	}
	else
	{
		ft_strdel(&tab[ms->k]);
		tab[ms->k] = ft_strdup(ms->right[ms->j++]);
	}
	ms->k++;
}

/*
** main entrypoint for mergesort
** The function pointer
** 		void (*f)(t_ls *ls, int i, int j, int k)
** is the sorting method to use.
*/

void	sort_merge(t_obj *ls, int l, int r, void (*f)(t_obj *ls, int i, int j, \
int k))
{
	int m;

	if (l < r)
	{
		m = l + (r - l) / 2;
		sort_merge(ls, l, m, f);
		sort_merge(ls, m + 1, r, f);
		f(ls, l, m, r);
	}
}
