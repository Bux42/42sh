/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 19:22:12 by videsvau          #+#    #+#             */
/*   Updated: 2018/03/08 15:40:01 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

void		print_converted(t_inp **inp, int type)
{
	t_inp		*cp;

	if ((cp = (*inp)))
	{
		while (cp)
		{
			ft_putchar(cp->c);
			cp = cp->next;
		}
		if (type & PIPE)
			ft_putstr(" <= PIPE");
		if (type & AND)
			ft_putstr(" <= AND");
		if (type & OR)
			ft_putstr(" <= OR");
		if (type & TOFILE)
			ft_putstr(" <= TOFILE");
		if (type & ATOFILE)
			ft_putstr(" <= ATOFILE");
		if (type & TOEXE)
			ft_putstr(" <= TOEXE");
		if (type & ARGUMENT)
			ft_putstr(" <= ARGUMENT");
		if (type & COMMAND)
			ft_putstr(" <= COMMAND");
		if (type & BUILTIN)
			ft_putstr(" <= BUILTIN");
		if (type & _FILE)
			ft_putstr(" <= FILE");
		if (type & SEMICOLON)
			ft_putstr(" <= SEMICOLON");
		custom_return();
	}
}

void		print_splitted(t_inpl **inpl)
{
	t_inpl	*cp;

	if ((cp = (*inpl)))
	{
		while (cp)
		{
			print_converted(&cp->inp, cp->type);
			cp = cp->next;
		}
	}
}
