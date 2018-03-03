/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_local.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drecours <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 14:49:26 by drecours          #+#    #+#             */
/*   Updated: 2018/03/03 14:39:29 by drecours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"
#include "builtin.h"

int		builtin_local(char **exec, t_sh *sh)
{
	t_loc	*cp;

	if (exec[1])
	{
		ft_putstr("local: Too many arguments.");
		custom_return();
		return (1);
	}
	cp = sh->loc;
	while (cp)
	{
		ft_putstr(cp->content);
		custom_return();
		cp = cp->next;
	}
	return (0);
}
