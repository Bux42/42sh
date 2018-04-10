/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 16:36:59 by videsvau          #+#    #+#             */
/*   Updated: 2018/04/10 13:52:28 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

int			empty_quote(int context, t_inp **inp)
{
	t_inp	*cp;

	cp = *inp;
	if (cp->c == '\'' && context & QUOTE)
		if (cp->next && cp->next->c == '\'')
			return (1);
	if (cp->c == '\"' && context & DQUOTE)
		if (cp->next && cp->next->c == '\"')
			return (1);
	if (cp->c == '\'' && !context)
		if (cp->next && cp->next->c == '\'')
			return (1);
	if (cp->c == '\"' && !context)
		if (cp->next && cp->next->c == '\"')
			return (1);
	return (0);
}

int			escaped(t_inp **inp)
{
	t_inp	*cp;
	int		odd;

	odd = 2;
	if ((cp = (*inp)))
	{
		while (cp->previous && cp->previous->c == '\\')
		{
			odd++;
			cp = cp->previous;
		}
	}
	return (odd % 2);
}

void		add_token(t_inpl **inpl, t_inp **cp, t_sh *sh)
{
	t_inp	*add;

	add = NULL;
	while (*cp)
	{
		if (check_quoting((*cp)->c) && !escaped(cp))
			sh->context = try_update_context((*cp)->c, sh->context);
		if (right_context(sh->context) && ending_char((*cp)->c) &&
				!escaped(cp))
			break ;
		while ((*cp) && empty_quote(sh->context, cp))
		{
			(*cp) = (*cp)->next->next;
			sh->context = 0;
		}
		if (!*cp)
			break ;
		inp_insert_posat_remake(&add, (*cp)->c);
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
		inp_insert_posat_remake(&add, (*cp)->c);
		(*cp) = (*cp)->next;
	}
	if (add)
		inpl_push_back(inpl, &add, 1);
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
