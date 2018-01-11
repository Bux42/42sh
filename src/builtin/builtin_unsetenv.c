/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unsetenv.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drecours <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 11:10:34 by drecours          #+#    #+#             */
/*   Updated: 2018/01/11 12:23:22 by drecours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

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

static int			delete_env(t_env **env, char *input)
{
	t_env  *cp;
	t_env  *tmp;

	tmp = NULL;
	cp = (*env);
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

int					builtin_unsetenv(char **exec, t_env **env)
{
	int		i;

	i = 1;
	if (!exec[1])
		return (err_msg("unsetenv: missing argument", "", -1));
	while (exec[i])
	{
		delete_env(env, exec[i]);
		i++;
	}
	return (1);
}


