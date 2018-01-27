/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_input_search.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 11:35:54 by videsvau          #+#    #+#             */
/*   Updated: 2018/01/27 05:24:03 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"
#include "../builtin/builtin.h"

void		add_delete_letter_search(t_sh *sh)
{
	char	*tab[3];

	tab[0] = "exit";
	tab[1] = "0";
	tab[2] = NULL;
	if (sh->buff[0] > 31 && sh->buff[0] <= 127)
	{
		if (sh->buff[0] != 127)
		{
			ft_putchar(sh->buff[0]);
			check_endline(sh);
			inp_insert_posat(&sh->his_search, sh->buff[0]);
		}
		else
			delete_letter(sh, &sh->his_search);
		ft_putstr_endline("): ", sh);
		custom_left(sh);
		custom_left(sh);
		custom_left(sh);
	}
	else if (sh->buff[0] == 4)
	{
		ft_putstr(tgetstr("ve", NULL));
		builtin_exit(tab, &sh->env);
	}
}

void		search_input(t_sh *sh)
{
	if (sh->search_pos)
		erase_previous_search(sh, &sh->search_pos->inp);
	if (sh->buff[0] == 18)
	{
		if (sh->search == 2)
			switch_search_mode(sh, &sh->his_search);
		print_search_backward(sh, &sh->his_search, &sh->history, 0);
	}
	else if (sh->buff[0] == 6)
	{
		if (sh->search == 1)
			switch_search_mode(sh, &sh->his_search);
		print_search_forward(sh, &sh->his_search, &sh->history, 0);
	}
	else if (sh->search == 1)
		print_search_backward(sh, &sh->his_search, &sh->history, 1);
	else if (sh->search == 2)
		print_search_forward(sh, &sh->his_search, &sh->history, 1);
}

void		treat_input_search(t_sh *sh)
{
	sh->pos_at = pos_at(&sh->his_search, 15);
	if (!check_dimentions(sh))
		return ;
	sh->width = tgetnum("co");
	if (!sh->buff[1])
	{
		if ((sh->buff[0] > 31 && sh->buff[0] <= 127) || sh->buff[0] == 4)
			add_delete_letter_search(sh);
		else if (sh->buff[0] == 27)
		{
			insert_search(sh, &sh->his_search, &sh->search_pos->inp);
			return ;
		}
		search_input(sh);
	}
	if (sh->tty)
		tty_debug(sh, &sh->inpl->inp);
	ft_bzero(sh->buff, 6);
}
