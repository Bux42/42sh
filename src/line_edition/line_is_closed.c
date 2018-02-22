/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_is_closed.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 15:26:20 by videsvau          #+#    #+#             */
/*   Updated: 2018/02/22 14:20:59 by videsvau         ###   ########.fr       */
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

int		print_expected_prompt(t_sh *sh, t_close **close)
{
	t_close		*cp;

	sh->posy = 1;
	if ((cp = *close))
	{
		while (cp->next)
			cp = cp->next;
		while (cp)
		{
			if (cp->flag & QUOTE)
				print_str("quote", sh);
			if (cp->flag & DQUOTE)
				print_str("dquote", sh);
			if (cp->flag & BQUOTE)
				print_str("bquote", sh);
			if (cp->previous)
			{
				print_str(" ", sh);
				cp = cp->previous;
			}
			else
				break ;
		}
	}
	print_str("> ", sh);
	return (0);
}

int		line_is_closed(t_sh *sh, t_inp **inp)
{
	t_inp	*cp;

	if ((cp = (*inp)))
	{
		while (cp)
		{
			if (cp->c == '\\')
			{
				if (cp->next)
				{
					if (cp->next->next)
						cp = cp->next->next;
					else
						return (1);
				}
				else
					return (print_expected_prompt(sh, &sh->close));
			}
			if (cp->c == '\'')
				check_context_quote(sh);
			if (cp->c == '`')
				check_context_bquote(sh);
			if (cp->c == '\"')
				check_context_dquote(sh);
			cp = cp->next;
		}
	}
	if (sh->close)
		return (print_expected_prompt(sh, &sh->close));
	return (1);
}
