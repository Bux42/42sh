/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_flag_vui.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drecours <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 12:57:37 by drecours          #+#    #+#             */
/*   Updated: 2018/04/05 06:00:17 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"
#include "builtin.h"

int			flag_v_u_i(char ***tab, char **exec, int *verbose)
{
	int		i;
	int		x;

	i = 0;
	while (exec[++i] && (exec[i][0] == '-' || (ft_strchr(exec[i], '=') &&
					exec[i][0] != '=')))
		if (exec[i][0] == '-')
		{
			x = 0;
			while (exec[i][++x])
			{
				if (exec[i][x] == 'v')
					nb_verb(verbose);
				else if (exec[i][x] == 'u' && (exec[i][x + 1] || exec[i + 1]))
				{
					unset_verb(*verbose, &exec[i][x], exec[i + 1], tab);
					if (!exec[i][x + 1])
						i++;
					break ;
				}
				else if (!ft_strchr("ivP-", exec[i][x]))
					return (illegal_opt(exec[i][x]));
			}
		}
	return (1);
}

int			flag_v(char **exec)
{
	int		i;
	int		x;

	i = 0;
	while (exec[++i] && (exec[i][0] == '-' || (ft_strchr(exec[i], '=') &&
					exec[i][0] != '=')))
		if (exec[i][0] == '-')
		{
			x = 0;
			while (exec[i][++x])
			{
				if (exec[i][x] == 'v')
					return (1);
				else if (exec[i][x] == 'u' && (exec[i][x + 1] || exec[i + 1]))
				{
					if (!exec[i][x + 1])
						i++;
					break ;
				}
			}
		}
	return (0);
}
