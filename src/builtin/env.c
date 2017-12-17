/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/17 08:45:58 by videsvau          #+#    #+#             */
/*   Updated: 2017/12/17 09:48:37 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

void		print_env(t_env **env)
{
	t_env	*cp;

	if ((cp = (*env)))
	{
		while (cp)
		{
			ft_putstr(cp->env);
			custom_return();
			cp = cp->next;
		}
	}
}

int			env(char **exec, t_env **env)
{
	if (exec)
		if (env)
			;
	if (!exec[1])
		print_env(env);
	return (1);
}
