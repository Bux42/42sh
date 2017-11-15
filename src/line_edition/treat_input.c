/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 03:52:19 by videsvau          #+#    #+#             */
/*   Updated: 2017/11/15 13:25:07 by videsvau         ###   ########.fr       */
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

	if (!(tgetent(NULL, TERM)))
		return (0);
	if (tgetnum("co") != sh->width)
	{
		new_size = tgetnum("co");
		if (new_size < sh->width)
		{
			if (sh->pos_at > new_size)
				sh->posy = sh->pos_at % new_size;
			if (sh->posy == 1)
			{
				ft_putchar(' ');
				ft_putstr(tgetstr("le", NULL));
			}
		}
		else
		{
			if (sh->pos_at > new_size)
				sh->posy = sh->pos_at % new_size;
			else
				sh->posy = sh->pos_at;
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
	sh->pos_at = pos_at(&sh->inpl->inp, sh->prompt_len);
	if (check_dimentions(sh))
		sh->width = tgetnum("co");
	else
		return ;
	if (!sh->buff[1])
	{
		if (sh->buff[0] > 31 && sh->buff[0] <= 127)
			add_delete_letter(sh);
		else
			check_shortcut(sh);
	}
	if (!sh->buff[3] && sh->buff[0] == 27 && sh->buff[1] == 91)
		move_cursor(sh, sh->buff[2]);
	if (sh->buff[0] == 27 && sh->buff[1] == 27 && sh->buff[2] == 91)
		jump_words(sh, sh->buff[3]);
	if (sh->buff[3] == 126 && sh->buff[2] == 51)
		delete_after(sh, &sh->inpl->inp);
	sh->inp_len = inp_list_len(&sh->inpl->inp);
	if (sh->tty)
		tty_debug(sh, &sh->inpl->inp);
	ft_bzero(sh->buff, 6);
}
