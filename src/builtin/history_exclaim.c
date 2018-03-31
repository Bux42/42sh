/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_exclaim.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drecours <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 11:23:58 by drecours          #+#    #+#             */
/*   Updated: 2018/03/30 23:41:53 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "../../inc/header.h"

int		next_is_false(t_inp **cp)
{
	t_inp	*inp;

	inp = *cp;
	if (!inp->next || inp->next->c == '"' || inp->next->c == '\\' ||
			inp->next->c == '(' || inp->next->c == '=' ||
			inp->next->c == ' ' || inp->next->c == '\t')
		return (1);
	return (0);
}

int		exclaim_surrounding(t_inp **inp)
{
	if ((*inp)->next->next)
	{
		if ((*inp)->next->next->c == '!')
			return (0);
	}
	return (1);
}

int		history_parsing(t_inp **inp, t_sh *sh)
{
	if ((*inp)->next->c == '!' && exclaim_surrounding(inp))
		return (last_command(sh, inp));
	else if ((*inp)->next->c == '-' && exclaim_surrounding(inp))
		return (get_his(sh, inp, 1));
	else if ((*inp)->next->c > 48 && (*inp)->next->c < 58 && exclaim_surrounding(inp))
		return (get_his(sh, inp, 2));
	else if ((*inp)->next->c == '?' && exclaim_surrounding(inp))
		return (get_his(sh, inp, 4));
	else
		return (get_his(sh, inp, 3));
	return (-1);
}

int		history_exclaim(t_inp **inp, t_sh *sh)
{
	t_inp	*cp;
	bool	quote;

	quote = 0;
	cp = *inp;
	while (cp && cp->c)
	{
		if (cp->c == '\'')
			quote = (quote) ? 0 : 1;
		if (!quote && cp->c == '!' && !(cp->previous &&
					cp->previous->c == '\\') && !next_is_false(&cp))
			if (history_parsing(&cp, sh) == -1)
				return (1);
		if (cp && cp->next)
			cp = cp->next;
		else
			break ;
	}
	while (cp && cp->previous)
		cp = cp->previous;
	*inp = cp;
	return (0);
}
