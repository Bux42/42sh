/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drecours <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 16:21:51 by drecours          #+#    #+#             */
/*   Updated: 2018/04/10 19:28:13 by videsvau         ###   ########.fr       */
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

static int	unset_err(char *key)
{
	ft_putstr_fd("unset: ", STDERR_FILENO);
	ft_putstr_fd(key, STDERR_FILENO);
	ft_putendl_fd(" key doesn't exist.", STDERR_FILENO);
	return (0);
}

static int	remove_loc_if(char *key, t_loc **local, char *builtin)
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
	if (ft_strcmp(builtin, "export"))
		unset_err(key);
	return (1);
}

int			builtin_unset(char **exec, t_sh *sh)
{
	int		i;

	i = 0;
	if (!exec[1] || too_big(exec))
	{
		ft_putendl_fd("Usage: unset [KEY ...]", 2);
		return (1);
	}
	while (exec[++i])
		if (valid_name(exec[i], "unset"))
		{
			if (remove_loc_if(exec[i], &sh->loc, exec[0]) == 1)
				return (2);
		}
		else
			return (3);
	return (0);
}
