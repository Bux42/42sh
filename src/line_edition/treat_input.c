/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 03:52:19 by videsvau          #+#    #+#             */
/*   Updated: 2017/11/13 10:02:15 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

int			pos_at(t_inp **inp, int prompt_size)
{
	t_inp	*cp;

	if ((cp = (*inp)))
	{
		while (cp)
		{
			prompt_size++;
			if (cp->pos == 2)
				return (prompt_size - 1);
			else if (cp->pos == 1)
				return (prompt_size);
			cp = cp->next;
		}
	}
	return (prompt_size);
}

int			check_dimentions(t_sh *sh)
{
	int		new_size;
	int		posat;

	if (!(tgetent(NULL, TERM)))
		return (0);
	if (tgetnum("co") != sh->width)
	{
		new_size = tgetnum("co");
		posat = pos_at(&sh->inpl->inp, sh->prompt_len);
		if (new_size < sh->width)
		{
			if (posat > new_size)
				sh->posy = posat % new_size;
			if (sh->posy == 1)
			{
				ft_putchar(' ');
				ft_putstr(tgetstr("le", NULL));
			}
		}
		else
		{
			if (posat > new_size)
			{
				sh->posy = posat % new_size;
			}
			else
				sh->posy = posat;
		}
	}
	return (1);
}

void		check_endline(t_sh *sh)
{
	if (sh->posy == sh->width)
	{
		sh->posy = 1;
		ft_putchar(' ');
		ft_putstr(tgetstr("le", NULL));
	}
	else
		sh->posy++;
}

void		treat_input(t_sh *sh)
{
	if (check_dimentions(sh))
		sh->width = tgetnum("co");
	else
		return ;
	if (sh->tty)
		tty_debug(sh, &sh->inpl->inp);
	if (!sh->buff[1] && sh->buff[0] != 9)
		add_delete_letter(sh);
	if (!sh->buff[3] && sh->buff[0] == 27 && sh->buff[1] == 91)
		move_cursor(sh, sh->buff[2]);
	if (sh->buff[0] == 27 && sh->buff[1] == 27 && sh->buff[2] == 91)
		jump_words(sh, sh->buff[3]);
	if (sh->buff[3] == 126 && sh->buff[2] == 51)
		delete_after(sh, &sh->inpl->inp);
	sh->pos_at = pos_at(&sh->inpl->inp, sh->prompt_len);
	if (sh->tty)
		tty_debug(sh, &sh->inpl->inp);
	ft_bzero(sh->buff, 6);
}
