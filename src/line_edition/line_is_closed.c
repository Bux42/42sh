/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_is_closed.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 15:26:20 by videsvau          #+#    #+#             */
/*   Updated: 2018/03/26 21:17:50 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

void	check_context_quote(t_sh *sh)
{
	if (!sh->close)
		s_close_add(QUOTE, &sh->close);
	else if (sh->close->flag == QUOTE)
		delete_last_close(&sh->close);
}

void	check_context_bquote(t_sh *sh)
{
	if (!sh->close)
		s_close_add(BQUOTE, &sh->close);
	else if (sh->close->flag == BQUOTE)
		delete_last_close(&sh->close);
	else if (sh->close->flag == DQUOTE && !sh->close->next)
		s_close_add(BQUOTE, &sh->close);
}

void	check_context_dquote(t_sh *sh)
{
	if (!sh->close)
		s_close_add(DQUOTE, &sh->close);
	else if (sh->close->flag == DQUOTE)
		delete_last_close(&sh->close);
	else if (sh->close->flag == BQUOTE && !sh->close->next)
		s_close_add(DQUOTE, &sh->close);
}

int		check_context_backslash(t_sh *sh)
{
	if (sh->close && sh->close->flag & QUOTE)
		return (0);
	return (1);
}

int		line_is_closed(t_sh *sh, t_inp **inp)
{
	t_inp	*cp;

	if ((cp = (*inp)))
	{
		while (cp)
		{
			if (cp->c == '\'')
				check_context_quote(sh);
			if (cp->c == '`')
				check_context_bquote(sh);
			if (cp->c == '\"')
				check_context_dquote(sh);
			if (cp->c == '\\' && check_context_backslash(sh))
			{
				if (cp->next)
					cp = cp->next;
				else
					return (print_expected_prompt(sh, &sh->close));
			}
			cp = cp->next;
		}
	}
	if (sh->close)
		return (print_expected_prompt(sh, &sh->close));
	return (1);
}
