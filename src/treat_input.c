/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 20:25:37 by videsvau          #+#    #+#             */
/*   Updated: 2017/11/04 20:45:52 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../inc/header.h"

void		restore_cursor_pos(t_inp **inp)
{
	t_inp	*cp;
	t_inp	*save;

	cp = (*inp);
	while (cp)
	{
		if (cp->pos)
		{
			if (cp->pos == 1)
				cp = cp->next;
			break ;
		}
		cp = cp->next;
	}
	save = cp;
	while (cp)
	{
		ft_putchar(cp->c);
		cp = cp->next;
	}
	while (save)
	{
		ft_putstr(tgetstr("le", NULL));
		save = save->next;
	}
}

void		treat_input(t_sh *sh)
{
	/*ft_putnbr(sh->buff[0]);
	ft_putchar(' ');
	ft_putnbr(sh->buff[1]);
	ft_putchar(' ');
	ft_putnbr(sh->buff[2]);
	ft_putchar(' ');
	ft_putnbr(sh->buff[3]);
	ft_putchar(' ');
	ft_putnbr(sh->buff[4]);
	*/if (!sh->buff[1] && sh->buff[0] != 10 && sh->buff[0] != 9)
	{
		if (sh->buff[0] == 127)
			delete_pos(&sh->inp);
		else
		{
			ft_putchar(sh->buff[0]);
			restore_cursor_pos(&sh->inp);
			inp_push_back(&sh->inp, sh->buff[0]);
		}
	}
	else
	{
		if (!sh->buff[1])
		{
			if (sh->buff[0] == 10)
				;
			if (sh->buff[0] == 9)
				if (!auto_completion(&sh->inp))
					restore_cursor_pos(&sh->inp);
		}
		else if (sh->buff[0] == 27 && sh->buff[1] == 91)
		{
			if (sh->buff[2] == 68)
				move_left(&sh->inp);
			else if (sh->buff[2] == 67)
				move_right(&sh->inp);
			else if (sh->buff[2] == 51 && sh->buff[3] == 126 && !sh->buff[4])
				delete_pos_a(&sh->inp);
			else if (sh->buff[2] == 70 && !sh->buff[3])
				home_end(&sh->inp, 0);
			else if (sh->buff[2] == 72 && !sh->buff[3])
				home_end(&sh->inp, 1);
		}
		else if (sh->buff[0] == 27 && sh->buff[1] == 27 && sh->buff[2] == 91)
		{
			if (!sh->buff[4])
			{
				if (sh->buff[3] == 68)
					jump_left_word(&sh->inp);
				if (sh->buff[3] == 67)
					jump_right_word(&sh->inp);
			}
		}
	}
	debug_file(&sh->inp);
	ft_bzero(sh->buff, 6);
}
