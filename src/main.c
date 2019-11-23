/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 20:27:49 by tvandivi          #+#    #+#             */
/*   Updated: 2019/11/22 18:29:16 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

t_lst	*set_lptr(char *rename)
{
	t_lst	*tmp;

	tmp = (t_lst *)malloc(sizeof(t_lst) * 1);
	tmp->name = ft_strdup(rename);
	lstat(tmp->name, &tmp->st);
	tmp->pw = getpwuid(tmp->st.st_uid);
	tmp->gr = getgrgid(tmp->st.st_gid);
	tmp->next = NULL;
	return (tmp);
}

t_lst *new_lptr(struct dirent **ident)
{
	t_lst			*lst;
	struct dirent 	*dent;

	if (!(*ident))
		return (NULL);
	dent = *ident;
	lst = (t_lst *)malloc(sizeof(t_lst) * 1);
	lst->name = ft_strdup(dent->d_name);
	lstat(lst->name, &lst->st);
	lst->pw = NULL;
	lst->gr = NULL;
	lst->pad_size = 0;
	lst->next = NULL;
	return (lst);
}

t_lst	*no_options(t_ls *ls)
{
	int		i;
	t_lst	*lptr;
	t_lst	*head;
	
	i = 0;
	ls->ddir = opendir(".");
	ls->dent = readdir(ls->ddir);
	lptr = new_lptr(&ls->dent);
	head = lptr;
	while (lptr)
	{
		ls->dent = readdir(ls->ddir);
		lptr->next = new_lptr(&ls->dent);
		lptr = lptr->next;
		i++;
	}
	ls->total = i;
	return (head);
}

t_lst	*get_node(t_lst *root, char *name)
{
	if (!root)
		return (NULL);
	while (root)
	{
		if (ft_strcmp(root->name, name) == 0)
			return (root);
		root = root->next;
	}
	return (root);
}

void    s_merge_reverse(t_ls *ls, int l, int m, int r)
{
    t_ms    ms;
	char	**tab;
	
	tab = ls->sort_table;
    ms_init(&ms, (m - l + 1), (r - m));
    copy_tab(&ms, l, m, tab);
    while (ms.i < ms.n1 && ms.j < ms.n2)
    {
		if (ft_strcmp(ms.right[ms.j], ms.left[ms.i]) > 0)
		{
			ft_strdel(&tab[ms.k]);
			tab[ms.k] = ft_strdup(ms.right[ms.j++]);
		}
		else
		{
			ft_strdel(&tab[ms.k]);
			tab[ms.k] = ft_strdup(ms.left[ms.i++]);
		}
		ms.k++;
    }
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

void    s_merge_forward(t_ls *ls, int l, int m, int r)
{
    t_ms    ms;
	char	**tab;

	tab = ls->sort_table;
    ms_init(&ms, (m - l + 1), (r - m));
    readin_table(&ms, tab, l, m);
    while (ms.i < ms.n1 && ms.j < ms.n2)
		sort_by_character(&ms, tab);
    read_remaing(&ms, tab);
}

void    sort_merge(t_ls *ls, int l, int r, void (*f)(t_ls *ls, int i, int j, int k))
{
    int 	m;

    if (l < r)
    {
        m = l + (r - l) / 2;
        sort_merge(ls, l, m, f);
        sort_merge(ls, m + 1, r, f);
        f(ls, l, m, r);
    }
}

void	fill_table(t_ls *ls, t_lst *lsta)
{
	int	i;

	i = 0;
	ls->sort_table = (char **)malloc(sizeof(char *) * ls->total);
	while (i < ls->total)
	{
		if (ls->flags[0] == 'a' && lsta->name[0] == '.')
		{
			ls->sort_table[i++] = ft_strdup(lsta->name);
			lsta = lsta->next;
		}
		else if (lsta->name[0] == '.')
		{
			ls->total--;
			lsta = lsta->next;
		}
		else
		{
			ls->sort_table[i++] = ft_strdup(lsta->name);
			lsta = lsta->next;
		}
	}

}

void	chose_algo(t_ls *ls)
{
	if (ls->flags[1] == 'r' && ls->flags[2] != 't')
		sort_merge(ls, 0, (ls->total - 1), s_merge_reverse);
	else if (ls->flags[1] == 'r' && ls->flags[2] == 't')
		sort_merge(ls, 0, (ls->total - 1), s_merge_time_reverse);
	else if (ls->flags[2] == 't')
		sort_merge(ls, 0, (ls->total - 1), s_merge_time_forward);
	else
		sort_merge(ls, 0, (ls->total - 1), s_merge_forward);
}

void	print_results(t_ls *ls)
{
	char	*tmp;
	t_lst	*lst;
	int		i;

	i = 0;
	while (i < ls->total)
	{
		lst = get_node(ls->lst, ls->sort_table[i]);
		if (lst->st.st_mode == 0)
			lstat(ls->sort_table[i], &lst->st);
		tmp = ft_strnew(16);
		tmp = ft_strncpy(tmp, ctime(&lst->st.st_mtimespec.tv_sec), 16);
		printf("%-12s %ld %-20s\n", ls->sort_table[i], lst->st.st_mtimespec.tv_sec, (tmp + 3));
		ft_strdel(&tmp);
		i++;
	}
	printf("\n");
}

void	sort_list(t_ls *ls)
{
	fill_table(ls, ls->lst);
	chose_algo(ls);
	print_results(ls);
}

void	init_ls(t_ls *ls)
{
	ls->total = 0;
	ft_memset(ls->flags, 0, 5);
	ls->scan_list = NULL;
	ls->dent = NULL;
	ls->pad_size = 0;
	ls->pw = NULL;
	ls->gr = NULL;
	ls->lst = NULL;
}

void	check_flags(t_ls *ls, char **av)
{
	int		i;
	char	a;
	
	i = 1;
	a = 0;
	if (ls && av)
	{
		if (av[1][0] == '0')
		{
			while (av[1][i] != '\0')
			{
				a = av[1][i];
				if (a == 'a')
					ls->flags[0] = 'a';
				if (a == 'r')
					ls->flags[1] = 'r';
				if (a == 't')
					ls->flags[2] = 't';
				if (a == 'R')
					ls->flags[3] = 'R';
				if (a == 'l')
					ls->flags[4] = 'l';
				i++;
			}
		}
	}
}

void	print_list(t_ls *ls, t_lst *lst)
{

	printf("total: %d\n", ls->total);
	while (lst)
	{
		printf("%-10s %o\n", lst->name, lst->st.st_mode);
		lst = lst->next;
	}
}

int	main(int ac, char **av)
{
	int 	i;
	int		j;
	t_ls	ls;

	i = 0;
	j = 0;
	init_ls(&ls);
	if (ac == 1)
	{
		ls.lst = no_options(&ls);
		i++;
		sort_list(&ls);
	}
	else
	{
		check_flags(&ls, av);
		ls.lst = no_options(&ls);
		sort_list(&ls);
	}

	return (0);
}