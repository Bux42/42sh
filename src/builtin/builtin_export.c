/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drecours <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 16:39:15 by drecours          #+#    #+#             */
/*   Updated: 2018/01/16 17:43:30 by drecours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"
#include "builtin.h"

int			export_it(t_env **env, t_loc **loc, char *key, char *name)
{
	char	*tab[3];
	(void)name;
	(void)loc;

	tab[0] = "export";
	tab[2] = NULL;
	tab[1] = key;
	builtin_setenv(tab, env);
	tab[1] = name;
	builtin_unset(tab, env, loc);
	return (1);
}

int			builtin_export(char **exec, t_env **env, t_loc **loc)
{
	t_loc	*cp;
	int		i;

	cp = *loc;
	i = 0;
	if (!exec[1])
		return (builtin_local(exec, env, loc));
	if (cp == NULL)
		return (1);
	while (exec[++i])
	{
		while (cp)
		{
			if (matching_name(cp->content, exec[i]))
			{
				export_it(env, loc, cp->content, exec[i]);
				break ;
			}
			cp = cp->next;
		}
		cp = *loc;
	}
	return (1);
}
