/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 01:20:53 by videsvau          #+#    #+#             */
/*   Updated: 2018/04/10 19:17:37 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

t_env		*new_env(char *env)
{
	t_env	*ret;

	if (!(ret = (t_env*)malloc(sizeof(t_env))))
		return (NULL);
	if (!(ret->env = ft_strdup(env)))
	{
		free(ret);
		return (NULL);
	}
	ret->next = NULL;
	return (ret);
}

void		env_push_back(t_env **envlist, char *env)
{
	t_env	*first;

	if (!(*envlist))
		(*envlist) = new_env(env);
	else
	{
		first = (*envlist);
		while (first->next)
			first = first->next;
		first->next = new_env(env);
	}
}

void		set_env(t_env **env, char *name, char *value)
{
	t_env	*cp;
	int		len;
	char	*new_env;

	len = ft_strlen(name) + ft_strlen(value);
	if (len > 10000 || !(new_env = (char*)malloc(sizeof(char) * (len + 1))))
		return ;
	ft_bzero(new_env, len);
	ft_strcat(new_env, name);
	if ((cp = (*env)) && value)
	{
		ft_strcat(new_env, value);
		while (cp)
		{
			if (ft_strncmp(name, cp->env, ft_strlen(name)) == 0)
			{
				free(cp->env);
				cp->env = new_env;
				return ;
			}
			cp = cp->next;
		}
	}
	env_push_back(env, new_env);
	free(new_env);
}
