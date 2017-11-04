/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 16:13:26 by videsvau          #+#    #+#             */
/*   Updated: 2017/11/04 21:57:24 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

int			valid_env(char *env)
{
	if (ft_strcmp(&env[5], "xterm") == 0)
		return (1);
	if (ft_strcmp(&env[5], "xterm-88color") == 0)
		return (1);
	if (ft_strcmp(&env[5], "xterm-256color") == 0)
		return (1);
	return (0);
}

int			matching_env(char *env, char *match)
{
	if (ft_strncmp(env, match, ft_strlen(match)) == 0)
		return (1);
	return (0);
}

char		*get_specific_env(char *env, t_env **envlist)
{
	t_env	*cp;

	if ((cp = (*envlist)))
	{
		while (cp)
		{
			if (ft_strncmp(env, cp->env, ft_strlen(env)) == 0)
				return (ft_strdup(cp->env));
			cp = cp->next;
		}
	}
	return (NULL);
}

int			get_env(char **env, t_sh *sh)
{
	int		i;
	int		valid;

	valid = 0;
	sh->env = NULL;
	sh->inp = NULL;
	sh->clipboard = NULL;
	ft_bzero(sh->buff, 6);
	i = -1;
	while (env[++i])
	{
		if (matching_env(env[i], "TERM="))
			if (valid_env(env[i]))
				valid++;
		env_push_back(&sh->env, env[i]);
	}
	return (valid);
}
