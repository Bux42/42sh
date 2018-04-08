/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 17:25:37 by videsvau          #+#    #+#             */
/*   Updated: 2018/04/08 08:43:10 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

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
			after = (*inp)->next->next;
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

	c = '\0';
	before = (*inp)->previous;
	if ((*inp)->next)
	{
		if ((*inp)->next->c == 'n')
			c = '\n';
		if ((*inp)->next->c == 't')
			c = '\t';
		rep_backslash(c, inp, &before);
	}
}

void		convert_dquote(t_inp **inp, t_sh *sh)
{
	t_inp	*previous;

	get_previous_inp(inp, &previous);
	while ((*inp)->c != '\"')
	{
		if ((*inp)->c == '$')
			try_insert_variable(inp, sh);
		if ((*inp)->c == '\\')
			convert_backslash_dquote(inp);
		if (!(*inp)->next)
			break ;
		(*inp) = (*inp)->next;
	}
	relink_with_end(inp);
}

void		convert_quote(t_inp **inp)
{
	t_inp	*previous;

	if (!(*inp)->next)
	{
		previous = (*inp)->previous;
		free(previous->next);
		previous->next = NULL;
		*inp = previous;
		return ;
	}
	get_previous_inp(inp, &previous);
	while ((*inp)->c != '\'')
	{
		if ((*inp)->c == '\\')
			convert_backslash_quote(inp);
		if (!(*inp)->next)
			break ;
		(*inp) = (*inp)->next;
	}
	relink_with_end(inp);
}
