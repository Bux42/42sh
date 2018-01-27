/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_search.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 10:05:11 by videsvau          #+#    #+#             */
/*   Updated: 2018/01/27 04:48:37 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

void		switch_search_mode(t_sh *sh, t_inp **his_search)
{
	int		i;
	t_inp	*cp;

	i = 14;
	while (i--)
		custom_left(sh);
	cp = *his_search;
	while (cp)
	{
		cp = cp->next;
		custom_left(sh);
	}
	if (sh->search == 1 && (sh->search = 2))
		ft_putstr_endline("fwd", sh);
	else if (sh->search == 2 && (sh->search = 1))
		ft_putstr_endline("bck", sh);
	i = 11;
	while (i--)
		custom_right(sh);
	cp = *his_search;
	while (cp)
	{
		cp = cp->next;
		custom_right(sh);
	}
}

void		erase_previous_search(t_sh *sh, t_inp **search_pos)
{
	t_inp	*cp;
	int		i;

	i = 0;
	if ((cp = (*search_pos)))
	{
		while (i++ < 3)
			custom_right(sh);
		erase_inp_spaces(sh, search_pos);
		ft_putchar(' ');
		check_endline(sh);
		cp = (*search_pos);
		while (cp)
		{
			custom_left(sh);
			cp = cp->next;
		}
		i = 0;
		while (i++ < 4)
			custom_left(sh);
	}
}

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
		erase_inp_spaces(sh, inp);
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
