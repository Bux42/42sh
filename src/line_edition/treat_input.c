/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 03:52:19 by videsvau          #+#    #+#             */
/*   Updated: 2017/11/12 09:21:56 by videsvau         ###   ########.fr       */
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
	if (!(tgetent(NULL, TERM)))
		return (0);
	if (tgetnum("co") != sh->width)
		;
	if (sh->width + 1 == sh->posy)
		ft_putchar(' ');
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
	if (!sh->buff[1])
		add_delete_letter(sh);
	if (!sh->buff[3] && sh->buff[0] == 27 && sh->buff[1] == 91)
		move_cursor(sh, sh->buff[2]);
	sh->pos_at = pos_at(&sh->inpl->inp, sh->prompt_len);
	if (sh->tty)
		tty_debug(sh, &sh->inpl->inp);
	ft_bzero(sh->buff, 6);
}
