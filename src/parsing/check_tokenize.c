/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tokenize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 09:52:18 by videsvau          #+#    #+#             */
/*   Updated: 2018/04/08 09:57:14 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

int			valid_condition(t_inpl **inpl)
{
	if ((*inpl)->previous && (*inpl)->next)
	{
		if ((*inpl)->previous->type < 128)
			return (0);
		if ((*inpl)->next->type < 128)
			return (0);
		if ((*inpl)->previous->type & SEMICOLON)
			return (0);
		if ((*inpl)->next->type & SEMICOLON)
			return (0);
		return (1);
	}
	return (0);
}

int			valid_tofile(t_inpl **inpl)
{
	if ((*inpl)->previous && (*inpl)->next)
	{
		if ((*inpl)->previous->type < 128)
			return (-1);
		if ((*inpl)->previous->type == 2048 || (*inpl)->next->type == 2048)
			return (-1);
	}
	return (1);
}

int			valid_file(t_inpl **inpl)
{
	int		fd;

	fd = -1;
	if ((*inpl)->previous && (*inpl)->next)
	{
		if ((*inpl)->previous->type == 2048)
			return (-1);
		if ((*inpl)->next->type == 2048)
			return (-1);
		if ((*inpl)->previous && (*inpl)->previous->type > 64 &&
				(*inpl)->previous->type < 1024)
			if ((*inpl)->next->type & _FILE)
				return (1);
	}
	else
		return (-1);
	return (fd);
}

int			keep_going(int type)
{
	if (type & SEMICOLON)
		return (0);
	if (type & BUILTIN)
		return (0);
	if (type & COMMAND)
		return (0);
	return (1);
}

int			is_redirection(int type)
{
	if (type & TOFILE)
		return (1);
	if (type & ATOFILE)
		return (1);
	if (type & TOEXE)
		return (1);
	if (type & HERE)
		return (1);
	if (type & AGGR)
		return (1);
	if (type & AGGRFILE)
		return (1);
	if (type & LAGGR)
		return (1);
	if (type & LAGGRIN)
		return (1);
	return (0);
}
