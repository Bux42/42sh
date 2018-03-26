/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 01:05:54 by videsvau          #+#    #+#             */
/*   Updated: 2018/03/26 21:59:26 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"
#include "../builtin/builtin.h"

char		*get_specific_env(char *env, t_env **envlist)
{
	t_env	*cp;

	if ((cp = (*envlist)))
	{
		while (cp)
		{
			if (ft_strncmp(env, cp->env, ft_strlen(env)) == 0)
				return (ft_strdup(&cp->env[ft_strlen(env)]));
			cp = cp->next;
		}
	}
	return (NULL);
}

char		*get_specific_loc(char *env, t_loc **envlist)
{
	t_loc	*cp;

	if ((cp = (*envlist)))
	{
		while (cp)
		{
			if (ft_strncmp(env, cp->content, ft_strlen(env)) == 0)
				return (ft_strdup(&cp->content[ft_strlen(env)]));
			cp = cp->next;
		}
	}
	return (NULL);
}

void		get_env(char **env, t_sh *sh)
{
	int		i;
	char	*shlvl;
	char	*setenv[2];
	int		shlvl_atoi;

	i = -1;
	sh->env = NULL;
	while (env[++i])
		env_push_back(&sh->env, env[i]);
	if ((shlvl = get_specific_env("SHLVL=", &sh->env)))
	{
		shlvl_atoi = ft_atoi(shlvl);
		free(shlvl);
		setenv[0] = ft_strdup("SHLVL=");
		setenv[1] = ft_itoa(shlvl_atoi + 1);
		set_env(&sh->env, setenv[0], setenv[1]);
		free(setenv[0]);
		free(setenv[1]);
	}
	else
		env_push_back(&sh->env, "SHLVL=1");
}
