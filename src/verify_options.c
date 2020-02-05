/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_options.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 15:58:07 by tvandivi          #+#    #+#             */
/*   Updated: 2020/02/04 15:42:58 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

/*
** The verify function only handles 'verification' of options.
** It iterates through the arguments provided by the user
** and only operates on arguments starting with the '-' character.
** The function breaks on first contact with a non-flag argument.
**
** Each argument that starts with the '-' character is then passed
** to the is_good_option function.
**
** The is_good_option static function only checks if the letters
** contained are valid flag characters.
**
** If the program encouters a bad option character, it immediately
** prints to stdout an error message and exits the program.
*/

static int		is_good_option(char *str)
{
	int	i;

	i = 1;
	while (str[i] != '\0')
	{
		if (str[i] == 'a' || str[i] == 't' || str[i] == 'l' \
			|| str[i] == 'r' || str[i] == 'R' || str[i] == 'c')
			i++;
		else
		{
			ft_putstr("ft_ls: Illegal option -- ");
			ft_putchar(str[i]);
			ft_putchar('\n');
			return (0);
		}
	}
	if (i > 0 && str[i] == '\0')
		return (1);
	return (0);
}

void			verify_options(int ac, char **av)
{
	int	i;

	i = 1;
	if (ac >= 2)
	{
		while (i < ac)
		{
			if (is_option(av[i]))
			{
				if (0 == is_good_option(av[i]))
				{
					exit(0);
				}
			}
			else
				break ;
			i++;
		}
	}
}
