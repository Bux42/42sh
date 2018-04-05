/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drecours <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 13:03:53 by drecours          #+#    #+#             */
/*   Updated: 2018/04/05 16:02:07 by drecours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "../../inc/header.h"

int		 match_name(char *env, char *name)
{
	int		i;

	i = 0;
	while (env[i] == name[i] && name[i] && env[i] && env[i] != '=')
		i++;
	if (name[i] == '\0' && env[i] == '=')
		return (1);
	return (0);
}

int		builtin_color(char **exec, t_sh *sh)
{
	char	*tab[3];

	tab[0] = "setenv";
	tab[1] = "CLICOLOR";
	tab[2] = NULL;
	if (exec[1] && exec[2])
		return (err_msg("color: ", "Too many arguments.", 1));
	if (!exec[1] || ft_strcmp(exec[1], "on") == 0)
	{
		tab[1] = "CLICOLOR=1";
		return (builtin_setenv(tab, sh));
	}
	else
		return (builtin_unsetenv(tab, sh));
	return (0);
}
