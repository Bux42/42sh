/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drecours <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 16:21:51 by drecours          #+#    #+#             */
/*   Updated: 2018/01/16 16:38:25 by drecours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "../../inc/header.h"

int			remove_between(t_loc **cp, t_loc **tmp)
{
	(*tmp)->next = (*cp)->next;
	free((*cp)->content);
	free((*cp));
	return (1);
}

int			remove_first(t_loc **env, t_loc **cp)
{
	(*env) = (*env)->next;
	free((*cp)->content);
	free((*cp));
	return (1);
}

int                     match_name(char *env, char *name)
{
	int		i;

	i = 0;
	while (env[i] == name[i] && name[i] && env[i] && env[i] != '=')
		i++;
	if (name[i] == '\0' && env[i] == '=')
		return (1);
	return (0);
}

static int	remove_loc_if(char *key, t_loc **local)
{
	t_loc	*cp;
	t_loc	*tmp;

	cp = (*local);
	tmp = NULL;
	while (cp)
	{
		if (match_name(cp->content, key))
		{
			if (tmp)
				remove_between(&cp, &tmp);
			else
				remove_first(local, &cp);
			return (0);
		}
		tmp = cp;
		cp = cp->next;
	}
	ft_putstr_fd("unset: ",STDERR_FILENO);
	ft_putstr_fd(key, STDERR_FILENO);
	ft_putstr_fd(" key doesn't exist.", STDERR_FILENO);
	return (1);
}

int		builtin_unset(char **exec, t_env **env, t_loc **loc)
{
	int		i;
	(void)env;

	i = 0;
	if (!exec[1])
	{
		ft_putstr("Usage: unset [KEY ...]");
		custom_return();
		return (0);
	}
	while (exec[++i])
		if (remove_loc_if(exec[i], loc) == 1)
			return (0);
	return (1);
}
