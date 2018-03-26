/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 01:05:54 by videsvau          #+#    #+#             */
/*   Updated: 2018/03/26 13:19:19 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

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

	i = -1;
	sh->env = NULL;
	while (env[++i])
		env_push_back(&sh->env, env[i]);
}
