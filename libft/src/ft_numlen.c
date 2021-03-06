/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_numlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/18 14:19:35 by tvandivi          #+#    #+#             */
/*   Updated: 2019/08/18 17:57:02 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_numlen(int nbr)
{
	int i;

	i = 1;
	while (nbr / 10 > 0)
	{
		i++;
		nbr /= 10;
	}
	return (i);
}
