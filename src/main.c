/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/31 10:37:04 by tvandivi          #+#    #+#             */
/*   Updated: 2020/01/04 14:40:41 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

/*
** initialize global structures
** struct ls:
** 		contains system library defined structure used for obtaining info on files and directories
** struct opt:
**		contains flags used to identify flags passed to program.
**
** Verify and set options else print error and exit.
**
** Verify arguments, print argument errors.
** Store argument batch 	  <---------<-------------<---------/
** Sort arguments						(r, t, a flags).	   /
** Get argument info 						   (l flag).	  /
** Output and read in next available arguments (R flag).     /
** LOOP: set arguments ->---------->---------->-------->----/ 
*/

static void	output_lookup(t_list *root)
{
	t_list *head;

	head = root;
	while (head)
	{
		ft_printf("content: %s\n", (char *)head->content);
		head = head->next;
	}
}

int		main(int ac, char **av)
{
	t_ls	ls;
	t_opt	opt;

	init_ls(&ls, ac);
	init_options(&opt);

	verify_options(ac, av);
	set_options(&opt, ac, av);
	
	verify_arguments(&ls, av, ac);
	set_arguments(&ls, &opt, av, ac);
	// sort_lookup();

	// while (1)
	// {
	// 	// dump to stdout
	// 	// check lookup/check R flag
	// }

	output_lookup(*(&(ls).lookup));
	if (DEBUG + 1)
		system("leaks ft_ls");
	return (0);
}