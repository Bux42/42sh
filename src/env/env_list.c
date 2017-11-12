/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 01:20:53 by videsvau          #+#    #+#             */
/*   Updated: 2017/11/12 02:20:59 by videsvau         ###   ########.fr       */
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
