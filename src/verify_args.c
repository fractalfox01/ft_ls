/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 10:18:55 by tvandivi          #+#    #+#             */
/*   Updated: 2020/01/03 13:50:25 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

/*
** The verify_arguments function verifies if the user passed arguments are
** valid (argument is a file or directory).
** If not, then the function prints an error to stdout and continues.
**
*/

void    verify_arguments(t_ls *ls, char **av, int ac)
{
    int i;

    i = (ac - 1);
    while (i > 0)
    {
        if (av[i][0] != OPTION)
        {
            stat(av[i], &ls->st);
            if (ls->st.st_mode <= 0)
            {
                ft_printf("ft_ls: %s: No such file or directory\n", av[i]);
            }
            ls->st.st_mode = 0;
        }
        i--;
    }
}