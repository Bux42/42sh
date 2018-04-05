/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_exclaim.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drecours <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 11:23:58 by drecours          #+#    #+#             */
/*   Updated: 2018/03/15 20:58:08 by drecours         ###   ########.fr       */
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

int		history_parsing(t_inp **cp, t_sh *sh)
{
	t_inp	*inp;

	inp = *cp;
	if (inp->next->c == '!')
		return (last_command(sh, cp));
	else if (inp->next->c == '-')
		return (by_last(sh, cp, 1));
	else if (inp->next->c <= '9' && inp->next->c >= '0')
		return (by_last(sh, cp, 2));
	else if (inp->next->c == '?')
		return (by_last(sh, cp, 4));
	else
		return (by_last(sh, cp, 3));
	return (0);
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
				return (-1);
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
