/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 17:25:37 by videsvau          #+#    #+#             */
/*   Updated: 2018/03/02 09:23:13 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

void		convert_bquote(t_inp **inp, t_sh *sh)
{
	*inp = *inp;
	sh->posy = sh->posy;
}

void		convert_backslash_quote(t_inp **inp)
{
	char	c;
	t_inp	*after;

	c = '\0';
	if ((*inp)->next)
	{
		if ((*inp)->next->c == '\n')
			c = '\n';
		if ((*inp)->next->c == '\t')
			c = '\t';
		if (c)
		{
			after = (*inp)->next->next;;
			(*inp)->c = c;
			free((*inp)->next);
			(*inp)->next = after;
			after->previous = (*inp);
		}
	}
}

void		convert_backslash_dquote(t_inp **inp)
{
	char	c;
	t_inp	*before;
	t_inp	*after;

	c = '\0';
	before = (*inp)->previous;
	if ((*inp)->next)
	{
		if ((*inp)->next->c == 'n')
			c = '\n';
		if ((*inp)->next->c == 't')
			c = '\t';
		if (c)
		{
			after = (*inp)->next->next;
			(*inp)->c = c;
			(*inp)->next = after;
			free(after->previous);
			after->previous = (*inp);
		}
		else
		{
			(*inp) = (*inp)->next;
			free((*inp)->previous);
			if (before)
				before->next = (*inp);
			(*inp)->previous = before;
		}
	}
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
		if ((*inp)->c == '\\')
			convert_backslash_dquote(inp);
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
	{
		if ((*inp)->c == '\\')
			convert_backslash_quote(inp);
		(*inp) = (*inp)->next;
	}
	after = (*inp)->next;
	(*inp) = (*inp)->previous;
	if (after)
		after->previous = (*inp);
	free((*inp)->next);
	(*inp)->next = after;
}
