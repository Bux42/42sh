/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_exclaim.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drecours <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 11:23:58 by drecours          #+#    #+#             */
/*   Updated: 2018/03/07 18:24:21 by drecours         ###   ########.fr       */
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
		ft_putstr("coin");
	else if (inp->next->c == '!')
		return (last_command(cp, sh, that));
	else if (inp->next->c == '-')
		by_last(cp, sh);
	else if (inp->next->c <= '9' && inp->next->c >= '0')
		by_first(cp, sh);
	else if (inp->next->c == '?')
		search_that(cp, sh);
	else
		search(cp, sh);
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
			if (history_parsing(inp, &cp, sh) == -1)
			return (-1);
		}
		cp = cp->next;
	}
	return (0);
}
