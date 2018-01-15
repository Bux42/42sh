/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_flag_equal_i.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drecours <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 15:51:01 by drecours          #+#    #+#             */
/*   Updated: 2018/01/15 17:02:30 by drecours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"
#include "builtin.h"

char	**flag_i(char **tab, char **exec, int verbose)
{
	int		i;
	int		x;

	i = 0;
	x = 0;
	while (exec[++i] && (exec[i][0] == '-' || !ft_strchr(exec[i], '=')))
		if (exec[i][0] == '-')
		{
			x = 1;
			while (exec[i][x])
			{
				if (exec[i][x] == 'u')
				{
					if (!exec[i][x + 1])
						i++;
					break ;
				}
				if (exec[i][x] == 'i')
				{
					if (verbose > 0)
					{
						ft_putstr("#env clearing environ");
						custom_return();
					}
					env_free(tab);
					if (!(tab = (char**)malloc(sizeof(char*) * 1)))
						return (NULL);
					tab[0] = NULL;
					return (tab);
				}
				x++;
			}
		}
	return (tab);
}
