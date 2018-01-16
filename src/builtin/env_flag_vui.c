/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_flag_vui.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drecours <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 12:57:37 by drecours          #+#    #+#             */
/*   Updated: 2018/01/16 14:28:06 by drecours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"
#include "builtin.h"

int			flag_v_u_i(char ***tab, char **exec, int *verbose)
{
	int		i;
	int		x;
	char	*str;
	char	*tmp;

	i = 1;
	x = 0;
	while (exec[i] && (exec[i][0] == '-' || (ft_strchr(exec[i], '=') &&
					exec[i][0] != '=')))
	{
		if (exec[i][0] == '-')
		{
			x = 1;
			while (exec[i][x])
			{
				if (exec[i][x] == 'v')
				{
					(*verbose)++;
					if (*verbose > 1)
					{
						ft_putstr("#env verbosity now at ");
						str = ft_itoa(*verbose);
						ft_putstr(str);
						free(str);
						custom_return();
					}
				}
				else if (exec[i][x] == 'u' && (exec[i][x + 1] || exec[i + 1]))
				{
					tmp = (exec[i][x + 1]) ? &exec[i][x + 1] : exec[i + 1];
					*tab = unsetenv_tab(*tab, tmp);
					if (*verbose > 0)
					{
						ft_putstr("#env unset:    ");
						ft_putstr(tmp);
						custom_return();
					}
					if (!exec[i][x + 1])
						i++;
					break ;
				}
				else if (exec[i][x] == 'u')
				{
					ft_putstr("env: option requires an argument -- u");
					custom_return();
				}
				else if (!ft_strchr("ivuP-", exec[i][x]))
				{
					ft_putstr("env: illegal option -- ");
					ft_putchar(exec[i][x]);
					custom_return();
					return (0);
				}
				x++;
			}
		}
		i++;
	}
	return (1);
}
