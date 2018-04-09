/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_set.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drecours <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 19:52:33 by drecours          #+#    #+#             */
/*   Updated: 2018/04/09 11:52:42 by drecours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"
#include "../builtin/builtin.h"

t_loc		*chain_local(char *str)
{
	t_loc		*chain;

	chain = NULL;
	if (!(chain = (t_loc*)malloc(sizeof(t_loc))))
		return (NULL);
	if (!ft_strchr(str, '='))
		chain->content = ft_strjoin(str, "=");
	else
		chain->content = ft_strdup(str);
	chain->next = NULL;
	return (chain);
}

int			matching_name(char *env, char *name)
{
	int		i;

	i = 0;
	while (env[i] == name[i] && name[i] && env[i] && env[i] != '=')
		i++;
	if (name[i] == '=' || env[i] == '=' || env[i] == '\0')
		return (1);
	return (0);
}

int			new_local(char *str, t_loc **local)
{
	t_loc	*cp;

	cp = *local;
	if (cp == NULL && ((*local) = chain_local(str)))
		return (1);
	while (cp && cp->content)
	{
		if (matching_name(cp->content, str))
		{
			free(cp->content);
			if (!ft_strchr(str, '='))
				cp->content = ft_strjoin(str, "=");
			else
				cp->content = ft_strdup(str);
			return (1);
		}
		if (cp->next == NULL)
			break ;
		cp = cp->next;
	}
	cp->next = chain_local(str);
	return (1);
}

int			builtin_set(char **exec, t_sh *sh)
{
	int		i;

	i = 1;
	if (!exec[1])
		return (builtin_local(exec, sh));
	while (exec[i])
	{
		if (exec[i][0] == '=')
		{
			ft_putendl_fd("set: Variable name must begin with a letter.", 2);
			return (1);
		}
		if (valid_name(exec[i], "set") == 0)
			return (3);
		new_local(exec[i], &sh->loc);
		i++;
	}
	return (0);
}
