/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_arguments.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 10:20:22 by tvandivi          #+#    #+#             */
/*   Updated: 2020/01/13 17:47:02 by tvandivi         ###   ########.fr       */
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

static int		stack_exist(t_stack *stack)
{
	if (stack)
		return (1);
	return (0);
}

static t_stack		*stack_add(t_stack *stack, char *d_name)
{
	t_stack	*tmp;

	if (stack_exist(stack))
	{
		tmp = (t_stack *)malloc(sizeof(t_stack) * 1);
		tmp->next = stack;
		tmp->name = ft_strdup(d_name);
		return (tmp);
	}
	else
	{
		stack = (t_stack *)malloc(sizeof(t_stack) * 1);
		stack->name = ft_strdup(d_name);
	}
	return (stack);
}

void    set_arguments(t_ls *ls, t_opt *opt, char **av, int ac)
{
    int             i;
    DIR             *dr;
    struct dirent   *dent;
    struct stat     st;

    i = 1;
    if (ac <= 2 && ((opt->set) || ac == 1))
    {
        dr = opendir(".");
        while ((dent = readdir(dr)))
        {
            if ((lstat(dent->d_name, &st)) == 0)
            {
                // ft_printf("%s\n", dent->d_name);
                if (st.st_mode >= S_IFDIR && st.st_mode < S_IFBLK && (ft_strcmp(dent->d_name, ".") != 0) && (ft_strcmp(dent->d_name, "..") != 0))
                    ls->stack = stack_add(ls->stack, dent->d_name);
            }
            dent = NULL;
        }
        // ft_printf("%s", "\n");
        closedir(dr);
    }
    else
    {
        while (i < ac && opt)
        {
            if (av[i][0] != OPTION)
            {
                if ((lstat(av[i], &st)) == 0)
                {
                    if (st.st_mode >= S_IFDIR && st.st_mode < S_IFBLK)
                    {
                        ls->stack = stack_add(ls->stack, av[i]);
                        ls->ls_args += 1;
                    }
                    else
                    {
                        ft_printf("%s\n", av[i]);
                    }
                }
                dent = NULL;
                // if (ls->st.st_mode >= S_IFDIR && ls->st.st_mode < S_IFBLK)
                //     {
                //         add_directory(ls, av[i]);
                //     }
                st.st_mode = 0;
            }
            i++;
        }
    }
}