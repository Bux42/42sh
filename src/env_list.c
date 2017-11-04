/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 16:37:36 by videsvau          #+#    #+#             */
/*   Updated: 2017/10/30 17:09:12 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

t_env		*new_env(char *env)
{
	t_env	*ret;

	if (!(ret = (t_env*)malloc(sizeof(t_env))))
		return (NULL);
	ret->env = ft_strdup(env);
	ret->next = NULL;
	return (ret);
}

void		env_push_back(t_env **env2, char *env)
{
	t_env	*first;

	first = (*env2);
	if (!first)
		(*env2) = new_env(env);
	else
	{
		while (first->next)
			first = first->next;
		first->next = new_env(env);
	}
}
