/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_sort_forward.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 19:01:32 by tvandivi          #+#    #+#             */
/*   Updated: 2020/01/15 13:37:57 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	time_sort_forward(t_ms *ms, char **tab)
{
	if (*ms->t1 == *ms->t2)
	{
		if (*ms->t3 >= *ms->t4)
		{
			ft_strdel(&tab[ms->k]);
			tab[ms->k] = ft_strdup(ms->left[ms->i++]);
		}
		else
		{
			ft_strdel(&tab[ms->k]);
			tab[ms->k] = ft_strdup(ms->right[ms->j++]);
		}
	}
	else
	{
		ft_strdel(&tab[ms->k]);
		tab[ms->k] = ft_strdup(ms->left[ms->i++]);
	}
}

void	sort_by_time_forward(t_obj *ls, t_ms *ms, char **tab)
{
	ms->l1 = get_node(ls->merger, ms->left[ms->i]);
	ms->l2 = get_node(ls->merger, ms->right[ms->j]);
	ms->t1 = &ms->l1->st.st_atimespec.tv_sec;
	ms->t2 = &ms->l2->st.st_atimespec.tv_sec;
	ms->t3 = &ms->l1->st.st_atimespec.tv_nsec;
	ms->t4 = &ms->l2->st.st_atimespec.tv_nsec;
	if (*ms->t1 >= *ms->t2)
		time_sort_forward(ms, tab);
	else
	{
		ft_strdel(&tab[ms->k]);
		tab[ms->k] = ft_strdup(ms->right[ms->j++]);
	}
	ms->k++;
}

void    s_merge_time_forward(t_obj *ls, int l, int m, int r)
{
    t_ms    ms;
	char	**tab;

	tab = ls->table;
    ms_init(&ms, (m - l + 1), (r - m));
    readin_table(&ms, tab, l, m);
    while (ms.i < ms.n1 && ms.j < ms.n2)
		sort_by_time_forward(ls, &ms, tab);
	read_remaing(&ms, tab);
}

void    s_merge_forward(t_obj *ls, int l, int m, int r)
{
    t_ms    ms;
	char	**tab;

	tab = ls->table;
    ms_init(&ms, (m - l + 1), (r - m));
    readin_table(&ms, tab, l, m);
    while (ms.i < ms.n1 && ms.j < ms.n2)
		sort_by_character(&ms, tab);
    read_remaing(&ms, tab);
}