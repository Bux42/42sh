/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_flag_vui.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drecours <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 12:57:37 by drecours          #+#    #+#             */
/*   Updated: 2018/01/15 15:21:23 by drecours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"
#include "builtin.h"

int			flag_v_u_i(char ***tab, char **exec)
{
	int		i;
	int		verbose;
	int		x;
	char	*tmp;

	i = 1;
	verbose = 0;
	x = 0;
	while (exec[i] && (exec[i][0] == '-' || !ft_strchr(exec[i], '=')))
	{
		if (exec[i][0] == '-')
		{
			x = 1;
			while (exec[i][x])
			{
				if (exec[i][x] == 'v')
				{
					verbose++;
					if (verbose > 1)
					{
						ft_putstr("#env verbosity now at ");
						ft_putstr(ft_itoa(verbose));
						custom_return();
					}
				}
				else if (exec[i][x] == 'u' && (exec[i][x + 1] || exec[i + 1]))
				{
					if (verbose > 0)
					{
						ft_putstr("#env unset:    ");
						tmp = (exec[i][x + 1]) ? &exec[i][x + 1] : exec[i + 1];
						ft_putstr(tmp);
						custom_return();
					}
					*tab = unsetenv_tab(*tab, tmp);
					if (exec[i][x + 1])
						return (0);
					i++;
				}
				else if (exec[i][x] == 'u')
				{
					ft_putstr("env: option requires an argument -- u");
					custom_return();
				}
				else if (!ft_strchr("ivuP", exec[i][x]))
				{
					ft_putstr("env: illegal option -- ");
					ft_putchar(exec[i][x]);
					custom_return();
					return (0);
				}
				x++;
			}
			i++;
		}
	}
	return (1);
}
