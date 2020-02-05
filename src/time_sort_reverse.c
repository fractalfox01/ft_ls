/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_sort_reverse.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 19:01:45 by tvandivi          #+#    #+#             */
/*   Updated: 2020/02/04 15:13:26 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	ls_sort_it(t_ms *ms, char **tab)
{
	if (ft_strcmp(ms->right[ms->j], ms->left[ms->i]) > 0)
	{
		ft_strdel(&tab[ms->k]);
		tab[ms->k] = ft_strdup(ms->right[ms->j++]);
	}
	else
	{
		ft_strdel(&tab[ms->k]);
		tab[ms->k] = ft_strdup(ms->left[ms->i++]);
	}
	ms->k++;
}

void	s_merge_time_reverse(t_obj *ls, int l, int m, int r)
{
	t_ms	ms;
	char	**tab;

	tab = ls->table;
	ms_init(&ms, (m - l + 1), (r - m));
	readin_table(&ms, tab, l, m);
	while (ms.i < ms.n1 && ms.j < ms.n2)
		sort_by_time_reverse(ls, &ms, tab);
	read_remaing(&ms, tab);
	free_ms(&ms);
}

void	s_merge_reverse(t_obj *ls, int l, int m, int r)
{
	t_ms	ms;
	char	**tab;

	tab = ls->table;
	ms_init(&ms, (m - l + 1), (r - m));
	copy_tab(&ms, l, m, tab);
	while (ms.i < ms.n1 && ms.j < ms.n2)
		ls_sort_it(&ms, tab);
	while (ms.i < ms.n1)
	{
		ft_strdel(&tab[ms.k]);
		tab[ms.k++] = ft_strdup(ms.left[ms.i++]);
	}
	while (ms.j < ms.n2)
	{
		ft_strdel(&tab[ms.k]);
		tab[ms.k++] = ft_strdup(ms.right[ms.j++]);
	}
	free_ms(&ms);
}
