/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_sort_forward.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 19:01:32 by tvandivi          #+#    #+#             */
/*   Updated: 2020/02/04 15:11:03 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	s_merge_time_forward(t_obj *ls, int l, int m, int r)
{
	t_ms	ms;
	char	**tab;

	tab = ls->table;
	ms_init(&ms, (m - l + 1), (r - m));
	readin_table(&ms, tab, l, m);
	while (ms.i < ms.n1 && ms.j < ms.n2)
		sort_by_time_forward(ls, &ms, tab);
	read_remaing(&ms, tab);
	free_ms(&ms);
}

void	s_merge_forward(t_obj *ls, int l, int m, int r)
{
	t_ms	ms;
	char	**tab;

	tab = ls->table;
	ms_init(&ms, (m - l + 1), (r - m));
	readin_table(&ms, tab, l, m);
	while (ms.i < ms.n1 && ms.j < ms.n2)
		sort_by_character(&ms, tab);
	read_remaing(&ms, tab);
	free_ms(&ms);
}
