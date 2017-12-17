/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whats_going_on.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 17:55:43 by videsvau          #+#    #+#             */
/*   Updated: 2017/12/13 03:16:11 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

int			working_context(int context, char c)
{
	if (c == '\'')
		if (context & DQUOTE)
			return (0);
	if (c == '\"')
	{
		if (context & QUOTE)
			return (0);
	}
	if (c == '$')
	{
		if (context & QUOTE)
			return (0);
	}
	if (c == ';')
	{
		if (context & QUOTE)
			return (0);
		if (context & DQUOTE)
			return (0);
	}
	if (c == '\0') // binary or option to binary
	{
		if (context & QUOTE)
			return (0);
		if (context & DQUOTE)
			return (0);
	}
	return (1);
}

int			normal_char(char c)
{
	if (c > 96 && c < 123)
		return (1);
	if (c == 95)
		return (1);
	if (c > 64 && c < 91)
		return (1);
	if (c > 44 && c < 58)
		return (1);
	return (0);
}

int			is_sep(t_inp **inp, t_inp *cp, int context)
{
	t_inp	*tmp;

	if ((tmp = (*inp)))
	{
		if (cp->c == ';')
		{
			if ((context & QUOTE) || (context & DQUOTE))
				return (0);
			else
			{
				custom_return();
				ft_putstr("New Command Line: ");
				(*inp) = (*inp)->next;
				return (1);
			}
		}
	}
	return (0);
}

void		lexer_parser(t_inp **inp, t_sh *sh)
{
	t_inp	*cp;

	sh->posy = sh->posy;
	if ((cp = (*inp)))
	{
		while (cp)
		{
			if (cp->c == '\'' && working_context(sh->context, cp->c))
				;
			if (cp->c == ';' && working_context(sh->context, cp->c))
				custom_return();
			ft_putchar(cp->c);
			cp = cp->next;
		}
	}
}