/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 20:25:37 by videsvau          #+#    #+#             */
/*   Updated: 2017/11/10 02:04:52 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../inc/header.h"

int			pos_at(t_inp **inp, int prompt_len)
{
	int		i;
	t_inp	*cp;

	i = prompt_len + 2;
	if ((cp = (*inp)))
	{
		while (cp)
		{
			if (cp->pos == 2)
				return (0);
			else if (cp->pos == 1)
				return (i);
			i++;
			cp = cp->next;
		}
	}
	return (i);
}

void		recalculate_cursor(t_sh *sh, int size, int cursor)
{
	if (sh->width > size)
	{
		if (cursor > size)
			sh->posy = cursor % size - 1;
	}
	else
	{
		if (cursor > size)
			sh->posy = cursor % size - 1;
		else
			sh->posy = cursor - 1;
	}
}

void		treat_input(t_sh *sh)
{
	if (!(tgetent(NULL, TERM)))
		return;
	sh->pos_at = pos_at(&sh->inp, sh->prompt_len);
	if (tgetnum("co") != sh->width)
	{
		recalculate_cursor(sh, tgetnum("co"), pos_at(&sh->inp, sh->prompt_len));
		sh->width = tgetnum("co");
	}
	if (!sh->buff[1] && sh->buff[0] != 10 && sh->buff[0] != 9)
	{
		if (sh->buff[0] == 127)
			delete_pos(&sh->inp);
		else
		{
			if (sh->posy == sh->width)
				sh->posy = 1;
			else
				sh->posy++;
			ft_putchar(sh->buff[0]);
			inp_push_back(&sh->inp, sh->buff[0]);
		}
	}
	else
	{
		if (!sh->buff[1])
			;
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
	debug_file(&sh->inp, sh);
	ft_bzero(sh->buff, 6);
}
