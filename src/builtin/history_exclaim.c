/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_exclaim.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drecours <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 11:23:58 by drecours          #+#    #+#             */
/*   Updated: 2018/03/15 19:59:40 by drecours         ###   ########.fr       */
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
/*	if (!inp->next || inp->next->c == '"' || inp->next->c == '\\' ||
			inp->next->c == '(' || inp->next->c == '=' ||
			inp->next->c == ' ' || inp->next->c == '\t')
	{
		ft_putstr("RIEN");
		*cp = (*cp)->next;
		return (0);
	}*/
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
		ft_putstr("coin");
		if (cp->c == '\'')
			quote = (quote) ? 0 : 1;
		if (!quote && cp->c == '!' && !(cp->previous &&
					cp->previous->c == '\\') && !next_is_false(&cp))
		{
			ft_putstr("here");
			custom_return();
			if (history_parsing(&cp, sh) == -1)
				return (-1);
		/*	if (cp && cp->next)
			{
				ft_putstr("SHOW");
				ft_putchar(cp->c);
				ft_putstr("TORTUE");
				cp = cp->next;
				ft_putchar(cp->c);
				ft_putstr("GERNOUILLE");
				ft_putchar(cp->previous->c);
				suppr_letter(&cp->previous);
				ft_putstr("GERNOUILLE");
			}
			else if (cp)
				suppr_letter(&cp);
		*/	ft_putstr("here");
			ft_putchar('a');
		//	if (cp && cp->c)
		//		ft_putchar('a');
			ft_putstr("SHOW");
			if (cp->next == NULL)
				break ;
			cp = cp->next;

		}
		else if (cp && cp->next)
			cp = cp->next;
		else
			break ;
	}
	ft_putstr("CE CODE ME GAVE");
	while (cp && cp->previous)
		cp = cp->previous;
	ft_putstr("CE CODE ME GAVE");
	ft_putchar(cp->c);
	//	inp = &cp;
	*inp = cp;
	ft_putchar((*inp)->c);
	cp = *inp;
	while (cp)
	{
		ft_putchar(cp->c);
		cp = cp->next;
	}
	ft_putstr("CE CODE ME GAVE");
	return (0);
}
