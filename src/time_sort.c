/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_sort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 18:22:45 by tvandivi          #+#    #+#             */
/*   Updated: 2019/11/22 18:26:11 by tvandivi         ###   ########.fr       */
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

void	sort_by_time_forward(t_ls *ls, t_ms *ms, char **tab)
{
	ms->l1 = get_node(ls->lst, ms->left[ms->i]);
	ms->l2 = get_node(ls->lst, ms->right[ms->j]);
	ms->t1 = &ms->l1->st.st_mtimespec.tv_sec;
	ms->t2 = &ms->l2->st.st_mtimespec.tv_sec;
	ms->t3 = &ms->l1->st.st_mtimespec.tv_nsec;
	ms->t4 = &ms->l2->st.st_mtimespec.tv_nsec;
	if (*ms->t1 >= *ms->t2)
		time_sort_forward(ms, tab);
	else
	{
		ft_strdel(&tab[ms->k]);
		tab[ms->k] = ft_strdup(ms->right[ms->j++]);
	}
	ms->k++;
}

void    s_merge_time_forward(t_ls *ls, int l, int m, int r)
{
    t_ms    ms;
	char	**tab;

	tab = ls->sort_table;
    ms_init(&ms, (m - l + 1), (r - m));
    readin_table(&ms, tab, l, m);
    while (ms.i < ms.n1 && ms.j < ms.n2)
		sort_by_time_forward(ls, &ms, tab);
	read_remaing(&ms, tab);
}

void	time_sort_reverse(t_ms *ms, char **tab)
{
	if (*ms->t1 == *ms->t2)
	{
		if (*ms->t4 <= *ms->t3)
		{
			ft_strdel(&tab[ms->k]);
			tab[ms->k] = ft_strdup(ms->right[ms->j++]);				}
		else
		{
			ft_strdel(&tab[ms->k]);
			tab[ms->k] = ft_strdup(ms->left[ms->i++]);
		}
	}
	else
	{
		ft_strdel(&tab[ms->k]);
		tab[ms->k] = ft_strdup(ms->right[ms->j++]);
	}
}

void	sort_by_time_reverse(t_ls *ls, t_ms *ms, char **tab)
{
	ms->l1 = get_node(ls->lst, ms->left[ms->i]);
	ms->l2 = get_node(ls->lst, ms->right[ms->j]);
	ms->t1 = &ms->l1->st.st_mtimespec.tv_sec;
	ms->t2 = &ms->l2->st.st_mtimespec.tv_sec;
	ms->t3 = &ms->l1->st.st_mtimespec.tv_nsec;
	ms->t4 = &ms->l2->st.st_mtimespec.tv_nsec;
	if (*ms->t2 <= *ms->t1)
		time_sort_reverse(&ms, tab);
	else
	{
		ft_strdel(&tab[ms->k]);
		tab[ms->k] = ft_strdup(ms->left[ms->i++]);
	}
	ms->k++;
}

void    s_merge_time_reverse(t_ls *ls, int l, int m, int r)
{
	t_ms    ms;
	char	**tab;

	tab = ls->sort_table;
    ms_init(&ms, (m - l + 1), (r - m));
	readin_table(&ms, tab, l, m);
    while (ms.i < ms.n1 && ms.j < ms.n2)
		sort_by_time_reverse(ls, &ms, tab);
    read_remaing(&ms, tab);
}