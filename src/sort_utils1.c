/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 12:36:24 by tvandivi          #+#    #+#             */
/*   Updated: 2020/02/03 20:12:23 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	tsr_helper(t_ms *ms, char **tab)
{
	if (*ms->t4 == *ms->t3)
	{
		if (ft_strcmp(ms->left[ms->i], ms->right[ms->j]) <= 0)
		{
			ft_strdel(&tab[ms->k]);
			tab[ms->k] = ft_strdup(ms->right[ms->j++]);
		}
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

void	tsf_helper(t_ms *ms, char **tab)
{
	if (*ms->t3 == *ms->t4)
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
	}
	else
	{
		ft_strdel(&tab[ms->k]);
		tab[ms->k] = ft_strdup(ms->left[ms->i++]);
	}
}

void	free_ms(t_ms *ms)
{
	ms->j = 0;
	ms->k = 0;
	if (ms->left)
	{
		while (ms->j < ms->n1)
		{
			ft_strdel(&ms->left[ms->j++]);
		}
		free(ms->left);
	}
	if (ms->right)
	{
		while (ms->k < ms->n2)
		{
			ft_strdel(&ms->right[ms->k++]);
		}
		free(ms->right);
	}
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

void	ms_init(t_ms *ms, int i, int j)
{
	ms->i = -1;
	ms->j = -1;
	ms->n1 = i;
	ms->n2 = j;
	ms->k = 0;
	ms->left = (char **)malloc(sizeof(char *) * i);
	ms->right = (char **)malloc(sizeof(char *) * j);
}
