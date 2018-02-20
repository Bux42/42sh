/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context_updater.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 01:33:43 by videsvau          #+#    #+#             */
/*   Updated: 2018/02/20 15:27:46 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

int			update_context(int context, int flag)
{
	if (context & flag)
		return (context - flag);
	return (context | flag);
}

void		dquote_inp(t_inp **cp, t_sh *sh)
{
	t_inp	*delimiter;

	delimiter = NULL;
	while ((*cp))
	{
		(*cp) = (*cp)->next;
	}
	lexer_parser(&delimiter, sh);
}

void		quote_inp(t_inp **cp, t_sh *sh)
{
	t_inp	*delimiter;

	delimiter = NULL;
	while ((*cp))
	{
		(*cp) = (*cp)->next;
	}
	lexer_parser(&delimiter, sh);
}

void		bquote_inp(t_inp **cp, t_sh *sh)
{
	t_inp	*delimiter;

	delimiter = NULL;
	while ((*cp))
	{
		if ((*cp)->c == '`')
		{
			(*cp) = (*cp)->next;
			break ;
		}
		else
			inp_insert_posat(&delimiter, (*cp)->c);
		(*cp) = (*cp)->next;
	}
	lexer_parser(&delimiter, sh);
}
