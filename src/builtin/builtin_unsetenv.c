/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unsetenv.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drecours <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 11:10:34 by drecours          #+#    #+#             */
/*   Updated: 2018/04/09 11:54:12 by drecours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"
#include "builtin.h"

static int			remove_between(t_env **cp, t_env **tmp)
{
	(*tmp)->next = (*cp)->next;
	free((*cp)->env);
	free((*cp));
	return (1);
}

static int			remove_first(t_env **env, t_env **cp)
{
	(*env) = (*env)->next;
	free((*cp)->env);
	free((*cp));
	return (1);
}

static int			delete_env(t_env **env, char *input, t_sh *sh)
{
	t_env	*cp;
	t_env	*tmp;

	tmp = NULL;
	cp = (*env);
	if (ft_strcmp("PATH", input) == 0)
	{
		hash_del(&sh->hash, sh);
		sh->hash = NULL;
	}
	while (cp)
	{
		if ((ft_strncmp(input, cp->env, ft_strlen(input))) == 0)
		{
			if (tmp)
				return (remove_between(&cp, &tmp));
			else
				return (remove_first(env, &cp));
		}
		tmp = cp;
		cp = cp->next;
	}
	return (1);
}

int					builtin_unsetenv(char **exec, t_sh *sh)
{
	int		i;
	t_env	**env;

	i = 1;
	env = &sh->env;
	if (!exec[1])
		return (err_msg("unsetenv: missing argument", "", 1));
	while (exec[i])
	{
		if (valid_name(exec[i], "unsetenv") == 0)
			return (3);
		delete_env(env, exec[i], sh);
		i++;
	}
	return (0);
}
