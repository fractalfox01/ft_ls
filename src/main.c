/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 20:27:49 by tvandivi          #+#    #+#             */
/*   Updated: 2019/11/23 21:09:27 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

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

t_lst	*has_options(t_ls *ls, char *name)
{
	int		i;
	t_lst	*lptr;
	t_lst	*head;
	
	i = 0;
	ls->ddir = opendir(name);
	if (ls->ddir)
	{
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
	return (NULL);
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

void	print_recursive(t_ls *ls)
{
	int		i;
	int		j;
	t_lst	*lst;
	t_ls	ls1;

	j = -1;
	i = 0;
	while (i < ls->total)
	{
		lst = get_node(ls->lst, ls->sort_table[i]);
		if (lst->st.st_mode > 0)
		{
			if (lst->st.st_mode >= S_IFDIR && lst->st.st_mode < S_IFBLK)
			{
				printf("\n./%s\n", ls->sort_table[i]);
				init_ls(&ls1);
				while (++j < 5)
					ls1.flags[j] = ls->flags[j];
				ls1.lst = has_options(&ls1, lst->name);
				sort_list(&ls1);
			}
			j = -1;
			i++;
		}
		// else
		// 	break ;
	}
}

void	print_results(t_ls *ls)
{
	char	*tmp;
	t_lst	*lst;
	size_t		pad;
	char	*s1;
	// char	*s2;
	int		i;

	i = 1;
	s1 = ft_strdup("%");
	lst = get_node(ls->lst, ls->sort_table[0]);
	pad = ft_strlen(lst->name);
	while (i < ls->total)
	{
		lst = get_node(ls->lst, ls->sort_table[i++]);
		if (pad < ft_strlen(lst->name))
			pad = ft_strlen(lst->name);
		ls->t_links += (uint64_t)lst->st.st_size;
	}
	printf("total %llu\n", (ls->t_links / 512));
	i = 0;
	while (i < ls->total)
	{
		lst = get_node(ls->lst, ls->sort_table[i]);
		// if (lst->st.st_mode < S_IFIFO)
		// 	lstat(ls->sort_table[i], &lst->st);
		// tmp = ft_strnew(16);
		// tmp = ft_strncpy(tmp, ctime(&lst->st.st_mtimespec.tv_sec), 16);
		printf("%-12s\n", ls->sort_table[i]);
		ft_strdel(&tmp);
		i++;
	}
	if (ls->flags[3] == 'R')
		print_recursive(ls);
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
	ls->t_links = 0;
	ls->dent = NULL;
	ls->pad_size = 0;
	ls->st.st_mode = 0;
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