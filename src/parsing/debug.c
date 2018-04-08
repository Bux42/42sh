/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 19:22:12 by videsvau          #+#    #+#             */
/*   Updated: 2018/04/08 06:55:09 by videsvau         ###   ########.fr       */
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
		print_t_inp(&cp);
		(type & HERE) ? ft_putstr(" <= HERE") : ft_putstr("");
		(type & PIPE) ? ft_putstr(" <= PIPE") : ft_putstr("");
		(type & AND) ? ft_putstr(" <= AND") : ft_putstr("");
		(type & OR) ? ft_putstr(" <= OR") : ft_putstr("");
		(type & TOFILE) ? ft_putstr(" <= TOFILE") : ft_putstr("");
		(type & ATOFILE) ? ft_putstr(" <= ATOFILE") : ft_putstr("");
		(type & TOEXE) ? ft_putstr(" <= TOEXE") : ft_putstr("");
		(type & ARGUMENT) ? ft_putstr(" <= ARGUMENT") : ft_putstr("");
		(type & COMMAND) ? ft_putstr(" <= COMMAND") : ft_putstr("");
		(type & BUILTIN) ? ft_putstr(" <= BUILTIN") : ft_putstr("");
		(type & _FILE) ? ft_putstr(" <= FILE") : ft_putstr("");
		(type & SEMICOLON) ? ft_putstr(" <= SEMICOLON") : ft_putstr("");
		(type & AGGR) ? ft_putstr(" <= AGGR") : ft_putstr("");
		(type & AGGRFILE) ? ft_putstr(" <= AGGR TOFILE") : ft_putstr("");
		(type & AGGROUT) ? ft_putstr(" <= AGGROUT") : ft_putstr("");
		(type & LAGGR) ? ft_putstr(" <= LAGGR") : ft_putstr("");
		(type & LAGGRIN) ? ft_putstr(" <= LAGGRIN") : ft_putstr("");
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
