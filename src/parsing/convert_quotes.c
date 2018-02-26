/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 17:25:37 by videsvau          #+#    #+#             */
/*   Updated: 2018/02/26 21:58:05 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

void		convert_bquote(t_inp **inp, t_sh *sh)
{
	if (*inp && sh)
		;
}

void		convert_dquote(t_inp **inp, t_sh *sh)
{
	t_inp	*previous;
	t_inp	*after;

	previous = (*inp)->previous;
	(*inp) = (*inp)->next;
	free((*inp)->previous);
	if (previous)
		previous->next = (*inp);
	(*inp)->previous = previous;
	while ((*inp)->c != '\"')
	{
		if ((*inp)->c == '$')
			try_insert_variable(inp, sh);
		(*inp) = (*inp)->next;
	}
	after = (*inp)->next;
	if (after)
		after->previous = (*inp)->previous;
	(*inp) = (*inp)->previous;
	free((*inp)->next);
	(*inp)->next = after;
}

void		convert_quote(t_inp **inp)
{
	t_inp	*previous;
	t_inp	*after;

	previous = (*inp)->previous;
	(*inp) = (*inp)->next;
	free((*inp)->previous);
	if (previous)
		previous->next = (*inp);
	(*inp)->previous = previous;
	while ((*inp)->c != '\'')
		(*inp) = (*inp)->next;
	after = (*inp)->next;
	(*inp) = (*inp)->previous;
	if (after)
		after->previous = (*inp);
	free((*inp)->next);
	(*inp)->next = after;
}
