/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_exclaim.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drecours <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 11:23:58 by drecours          #+#    #+#             */
/*   Updated: 2018/03/09 15:29:44 by drecours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "../../inc/header.h"

int		history_parsing(t_inp **that, t_inp **cp, t_sh *sh)
{
	t_inp	*inp;

	inp = *cp;
	if (!inp->next || inp->next->c == '"' || inp->next->c == '\\' ||
			inp->next->c == '(' || inp->next->c == '=' ||
			inp->next->c == ' ' || inp->next->c == '\t')
		return (0);
	else if (inp->next->c == '!')
		return (last_command(&inp, sh, that));
	else if (inp->next->c == '-')
		return (by_last(cp, sh, that, 1));
	else if (inp->next->c <= '9' && inp->next->c >= '0')
		return (by_last(cp, sh, that, 2));
	else if (inp->next->c == '?')
		return (by_last(cp, sh, that, 4));
	else
		return (by_last(cp, sh, that, 3));
	return (0);
}

int		history_exclaim(t_inp **inp, t_sh *sh)
{
	t_inp	*cp;
	bool	quote;

	quote = 0;
	cp = *inp;
	while (inp && cp)
	{
		if (cp->c == '\'')
			quote = (quote) ? 0 : 1;
		if (!quote && cp->c == '!' && !(cp->previous &&
					cp->previous->c == '\\'))
		{
			custom_return();
			if (history_parsing(inp, &cp, sh) == -1)
				return (-1);
		}
		cp = cp->next;
	}
	return (0);
}
