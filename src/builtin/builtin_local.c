/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_local.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drecours <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 14:49:26 by drecours          #+#    #+#             */
/*   Updated: 2018/04/05 13:10:22 by drecours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"
#include "builtin.h"

int		builtin_local(char **exec, t_sh *sh)
{
	t_loc	*cp;

	if (exec[1])
	{
		ft_putendl_fd("local: Too many arguments.", 2);
		return (1);
	}
	cp = sh->loc;
	while (cp)
	{
		ft_putendl(cp->content);
		cp = cp->next;
	}
	return (0);
}
