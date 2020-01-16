/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/31 10:37:04 by tvandivi          #+#    #+#             */
/*   Updated: 2020/01/13 19:13:08 by tvandivi         ###   ########.fr       */
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

void	sort_lookup()
{
	ft_printf("%sing\n", "test");
}

// char	*prepend_info(char *file, t_opt *opt, t_ls *ls)
// {
// 	if (file && opt && ls)
// 	{
		
// 	}
// 	if (opt->f_all)
// 	{

// 	}
// }

// static void	output_lookup(t_ls *ls, t_opt *opt)
// {
// 	t_list	*head;
// 	// char	*text;

// 	head = ls->lookup;
// 	while (head)
// 	{
// 		if (opt->set)
// 		{
// 			// text = prepend_info((char *)head->content, opt, ls);
// 		}
// 		ft_printf("%s\n", (char *)head->content);
// 		head = head->next;
// 	}
// }
int		stack_exist(t_stack *stack)
{
	if (stack)
		return (1);
	return (0);
}

t_stack		*stack_add(t_stack *stack, char *d_name)
{
	t_stack	*tmp;

	if (stack_exist(stack))
	{
		tmp = (t_stack *)malloc(sizeof(t_stack) * 1);
		tmp->next = stack;
		ft_memcpy(tmp->dir_name, d_name, ft_strlen(d_name));
		tmp->dir_name[ft_strlen(d_name)] = '\0';
		return (tmp);
	}
	else
	{
		stack = (t_stack *)malloc(sizeof(t_stack) * 1);
		ft_memcpy(stack, d_name, ft_strlen(d_name));
		stack->dir_name[ft_strlen(d_name)] = '\0';
	}
	return (stack);
}

t_stack	*ret_dir(char *directory)
{
	t_stack			*stack;
	DIR				*dr;
	struct dirent	*dent;
	struct stat		st;

	stack = NULL;
	dr = opendir(directory);
	if (dr && ft_strcmp(directory, ".") != 0 && ft_strcmp(directory, "..") != 0)
	{
		ft_printf("\n\n%s:\n", directory);
		while ((dent = readdir(dr)))
		{
			ft_printf("dent: %c\n", dent->d_type);
			if (lstat(dent->d_name, &st) == 0)
			{
				if (st.st_mode >= S_IFDIR && st.st_mode < S_IFBLK)
					stack = stack_add(stack, dent->d_name);
				ft_printf("%s\n", dent->d_name);
			}
		}
		ft_printf("%s", "\n");
		closedir(dr);
	}
	return (stack);
}

void	listdir()
{
	
}

int		main(int ac, char **av)
{
	/*
	** NEW MAIN AT RECURSE_EXAMPLE.C
	** pulling all parts together in the main
	** used for testing recursive implementation.
	*/
	t_ls	ls;
	t_opt	opt;
	t_stack	*stack;

	stack = NULL;
	init_ls(&ls, ac);
	init_options(&opt);

	verify_options(ac, av);
	set_options(&opt, ac, av);
	
	verify_arguments(av, ac);
	set_arguments(&ls, &opt, av, ac);
	
	print_ls(&ls.stack, &opt, av, ac);

	// while (1)
	// {
	// 	dump to stdout
	// 	check lookup/check R flag
	// 	output_lookup(*(&(ls).lookup));
	// }

	ls_free_all(&ls);
	// if (DEBUG + 1)
	// 	system("leaks ft_ls");
	return (0);
}