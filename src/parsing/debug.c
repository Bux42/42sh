/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 19:22:12 by videsvau          #+#    #+#             */
/*   Updated: 2018/04/02 19:35:04 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

void		print_t_inp(t_inp **inp)
{
	t_inp	*cp;

	if ((cp = (*inp)))
	{
		while (cp)
		{
			ft_putchar(cp->c);
			cp = cp->next;
		}
	}
}

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
		if (type & HERE)
			ft_putstr(" <= HERE");
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
		if (type & AGGR)
			ft_putstr(" <= AGGR");
		if (type & AGGRFILE)
			ft_putstr(" <= AGGR TOFILE");
		if (type & AGGROUT)
			ft_putstr(" <= AGGROUT");
		if (type & LAGGR)
			ft_putstr(" <= LAGGR");
		if (type & LAGGRIN)
			ft_putstr(" <= LAGGRIN");
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
