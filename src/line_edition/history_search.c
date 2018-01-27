/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_search.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 10:05:11 by videsvau          #+#    #+#             */
/*   Updated: 2018/01/27 02:49:59 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

void		erase_inp(t_sh *sh, t_inp **inp)
{
	t_inp	*cp;
	int		i;

	home_end(sh, &sh->inpl->inp, 0);
	ft_putstr(tgetstr("cr", NULL));
	i = 0;
	while (i++ < sh->prompt_len)
	{
		ft_putchar(' ');
		check_endline(sh);
	}
	if ((cp = (*inp)))
	{
		while (cp)
		{
			ft_putchar(' ');
			check_endline(sh);
			cp = cp->next;
		}
		cp = (*inp);
		while (cp)
		{
			custom_left(sh);
			cp = cp->next;
		}
	}
	i = 0;
	while (i++ < sh->prompt_len)
		custom_left(sh);
	sh->posy = 1;
}

void		ft_putstr_endline(char *str, t_sh *sh)
{
	int		i;

	i = 0;
	while (str[i])
	{
		ft_putchar(str[i++]);
		check_endline(sh);
	}
}

void		history_search(t_sh *sh)
{
	erase_inp(sh, &sh->inpl->inp);
	while (sh->history && sh->history->previous)
		sh->history = sh->history->previous;
	if (sh->buff[0] == 6 && (sh->search = 2))
		ft_putstr_endline("fwd-i-search (", sh);
	else if ((sh->search = 1))
		ft_putstr_endline("bck-i-search (", sh);
	while (sh->his_search)
	{
		ft_putchar(sh->his_search->c);
		check_endline(sh);
		if (sh->his_search->next)
			sh->his_search = sh->his_search->next;
		else
			break ;
	}
	ft_putstr_endline("): ", sh);
	custom_left(sh);
	custom_left(sh);
	custom_left(sh);
	while (sh->his_search && sh->his_search->previous)
		sh->his_search = sh->his_search->previous;
	ft_putstr(tgetstr("vi", NULL));
}
