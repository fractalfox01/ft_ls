/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_sort_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 15:12:14 by tvandivi          #+#    #+#             */
/*   Updated: 2020/02/05 22:43:46 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	time_sort_reverse(t_ms *ms, char **tab)
{
	if ((long)*ms->t1 == (long)*ms->t2)
	{
		if ((long)*ms->t4 <= (long)*ms->t3)
			tsr_helper(ms, tab);
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

void	sort_by_ctime_reverse(t_obj *ls, t_ms *ms, char **tab)
{
	ms->l1 = get_node(ls->merger, ms->left[ms->i]);
	ms->l2 = get_node(ls->merger, ms->right[ms->j]);
	ms->t1 = &ms->l1->st.st_ctime;
	ms->t2 = &ms->l2->st.st_ctime;
	ms->t3 = &ms->l1->st.st_ctimespec.tv_nsec;
	ms->t4 = &ms->l2->st.st_ctimespec.tv_nsec;
	if (*ms->t2 <= *ms->t1)
		time_sort_reverse(ms, tab);
	else
	{
		ft_strdel(&tab[ms->k]);
		tab[ms->k] = ft_strdup(ms->left[ms->i++]);
	}
	ms->k++;
}

void	sort_by_time_reverse(t_obj *ls, t_ms *ms, char **tab)
{
	ms->l1 = get_node(ls->merger, ms->left[ms->i]);
	ms->l2 = get_node(ls->merger, ms->right[ms->j]);
	ms->t1 = &ms->l1->st.st_mtimespec.tv_sec;
	ms->t2 = &ms->l2->st.st_mtimespec.tv_sec;
	ms->t3 = &ms->l1->st.st_mtimespec.tv_nsec;
	ms->t4 = &ms->l2->st.st_mtimespec.tv_nsec;
	if (*ms->t2 <= *ms->t1)
		time_sort_reverse(ms, tab);
	else
	{
		ft_strdel(&tab[ms->k]);
		tab[ms->k] = ft_strdup(ms->left[ms->i++]);
	}
	ms->k++;
}

void	s_merge_ctime_reverse(t_obj *ls, int l, int m, int r)
{
	t_ms	ms;
	char	**tab;

	tab = ls->table;
	ms_init(&ms, (m - l + 1), (r - m));
	readin_table(&ms, tab, l, m);
	while (ms.i < ms.n1 && ms.j < ms.n2)
		sort_by_ctime_reverse(ls, &ms, tab);
	read_remaing(&ms, tab);
	free_ms(&ms);
}
