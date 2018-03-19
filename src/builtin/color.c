/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drecours <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 13:03:53 by drecours          #+#    #+#             */
/*   Updated: 2018/03/19 13:14:16 by drecours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "../../inc/header.h"

int		builtin_color(char **exec, t_sh *sh)
{
	char	*tab[3];

	tab[0] = "setenv";
	tab[1] = "CLICOLOR";
	tab[2] = NULL;;
	if (exec[1] && exec[2])
		return (err_msg("color: ", "Too many arguments.", 1));
	if (!exec[1] || ft_strcmp(exec[1], "on") == 0)
	{
		tab[2] = "1";
		return (builtin_setenv(tab, sh));
	}
	else
		return (builtin_unsetenv(tab, sh));
	return (0);
}