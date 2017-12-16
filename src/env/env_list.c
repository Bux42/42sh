/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 01:20:53 by videsvau          #+#    #+#             */
/*   Updated: 2017/12/16 11:10:46 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

t_env		*new_env(char *env)
{
	t_env	*ret;

	if (!(ret = (t_env*)malloc(sizeof(t_env))))
		return (NULL);
	ret->env = ft_strdup(env);
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

	if ((cp = (*env)))
	{
		if (value)
			;
		while (cp)
		{
			if (ft_strncmp(name, cp->env, ft_strlen(name)) == 0)
				ft_putstr(cp->env);
			cp = cp->next;
		}
	}
}
