/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_local.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drecours <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 14:49:26 by drecours          #+#    #+#             */
/*   Updated: 2018/01/16 15:12:42 by drecours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"
#include "builtin.h"

int		builtin_local(char **exec, t_env **env, t_loc **loc)
{
	(void)env;
	(void)exec;
	t_loc	*cp;

	if (exec[1])
	{
		ft_putstr("local: Too many arguments.");
		custom_return();
		return (0);
	}
	cp = *loc;
	while (cp)
	{
		ft_putstr(cp->content);
		custom_return();
		cp = cp->next;
	}
	return (1);
}
