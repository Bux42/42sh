/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 16:36:59 by videsvau          #+#    #+#             */
/*   Updated: 2018/02/28 23:43:43 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

int			right_context(int flag)
{
	if (flag & QUOTE)
		return (0);
	if (flag & BQUOTE)
		return (0);
	if (flag & DQUOTE)
		return (0);
	return (1);
}

int			check_quoting(char c)
{
	if (c == '\'')
		return (1);
	if (c == '\"')
		return (1);
	if (c == '`')
		return (1);
	return (0);
}

int			ending_char(char c)
{
	if (c == ' ')
		return (1);
	if (c == '\t')
		return (1);
	if (c == '|')
		return (1);
	if (c == '&')
		return (1);
	if (c == '>')
		return (1);
	if (c == '<')
		return (1);
	return (0);
}

int			ending_special_char(char c)
{
	if (c == ' ' || c == '\t' || c == '\'' || c == '\"' || c == '`')
		return (1);
	if (c < 123 && c > 96)
		return (1);
	if (c < 96 && c > 64)
		return (1);
	if (c < 48 && c > 44)
		return (1);
	return (0);
}

void		add_token(t_inpl **inpl, t_inp **cp, t_sh *sh)
{
	t_inp	*add;

	add = NULL;
	while (*cp)
	{
		if (check_quoting((*cp)->c))
			sh->context = try_update_context((*cp)->c, sh->context);
		if (right_context(sh->context) && ending_char((*cp)->c))
			break ;
		inp_insert_posat(&add, (*cp)->c);
		(*cp) = (*cp)->next;
	}
	if (add)
		inpl_push_back(inpl, &add, 0);
}

void		add_special_token(t_inpl **inpl, t_inp **cp)
{
	t_inp	*add;

	add = NULL;
	while (*cp)
	{
		if (ending_special_char((*cp)->c))
			break ;
		inp_insert_posat(&add, (*cp)->c);
		(*cp) = (*cp)->next;
	}
	if (add)
		inpl_push_back(inpl, &add, 1);
}

int			special_tok(char c)
{
	if (c == '>')
		return (1);
	if (c == '<')
		return (1);
	if (c == '|')
		return (1);
	if (c == '&')
		return (1);
	return (0);
}

int			redir(t_inp *cp)
{
	if (cp->c > 47 && cp->c < 58)
		if (cp->next && cp->next->c == '>')
			return (1);
	return (0);
}

void		split_line(t_inpl **inpl, t_inp **clean, t_sh *sh)
{
	t_inp	*cp;

	cp = *clean;
	while (cp)
	{
		while (cp && cp->c == ' ')
			cp = cp->next;
		if (!cp)
			break ;
		if (special_tok(cp->c) || redir(cp))
			add_special_token(inpl, &cp);
		else
			add_token(inpl, &cp, sh);
	}
}
