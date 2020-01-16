/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 10:18:55 by tvandivi          #+#    #+#             */
/*   Updated: 2020/01/13 18:57:09 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

/*
** The verify_arguments function verifies if the user passed arguments are
** valid (argument is a file or directory).
** If not, then the function prints an error to stdout and continues.
**
*/

t_stack    *verify_arguments(char **av, int ac)
{
    t_stack *tmp;
    struct stat st;
    int i;

    tmp = NULL;
    i = (ac - 1);
    while (i > 0)
    {
        if (av[i][0] != OPTION)
        {
            lstat(av[i], &st);
            if (st.st_mode <= 0)
            {
                ft_printf("ft_ls: %s: No such file or directory\n", av[i]);
            }
            tmp = stack_push(&tmp, av[i]);
            st.st_mode = 0;
        }
        i--;
    }
    return (tmp);
}