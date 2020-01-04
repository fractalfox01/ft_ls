/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_arguments.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 10:20:22 by tvandivi          #+#    #+#             */
/*   Updated: 2020/01/04 14:41:57 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

/*
** The set_arguments function initially populates the lookup list
** with user provided arguments.
** If user provided arguments are null, then the current working 
** directory is added to the list.
**
** This function also takes into consideration of the recursive flag.
** If the recursive flag is set then the lookup list is also updated
** 
*/

void    add_file(t_ls *ls, char *file)
{
    t_list  *tmp;

    tmp = ft_lstnew(file, sizeof(char *));
    ft_lstadd(&ls->lookup, tmp);
}

void    set_arguments(t_ls *ls, t_opt *opt, char **av, int ac)
{
    int i;

    i = 1;
    if (ac <= 2 && ((opt->set) || ac == 1))
    {
        ls->dr = opendir(".");
        while ((ls->dent = readdir(ls->dr)))
        {
            ft_printf("%s\n", ls->dent->d_name);
            ls->dent = NULL;
        }
    }
    else
    {
        while (i < ac && opt)
        {
            if (av[i][0] != OPTION)
            {
                stat(av[i], &ls->st);
                if (ls->st.st_mode > 0)
                {
                    add_file(ls, av[i]);
                }
                ls->st.st_mode = 0;
            }
            i++;
        }
    }
}