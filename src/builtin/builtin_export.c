/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drecours <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 16:39:15 by drecours          #+#    #+#             */
/*   Updated: 2018/02/26 13:47:13 by drecours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"
#include "builtin.h"

int			export_it(t_sh *sh, char *key, char *name)
{
	char	*tab[3];
	(void)name;

	tab[0] = "export";
	tab[2] = NULL;
	tab[1] = key;
	builtin_setenv(tab, sh);
	tab[1] = name;
	return (builtin_unset(tab, sh));
}

int			builtin_export(char **exec, t_sh *sh)
{
	t_loc	*cp;
	int		i;

	cp = sh->loc;
	i = 0;
	if (!exec[1])
		return (builtin_local(exec, sh));
	if (cp == NULL)
		return (0);
	while (exec[++i])
	{
		while (cp)
		{
			if (matching_name(cp->content, exec[i]))
			{
				export_it(sh, cp->content, exec[i]);
				break ;
			}
			cp = cp->next;
		}
		cp = sh->loc;
	}
	return (0);
}
