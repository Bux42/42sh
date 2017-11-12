/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 03:52:19 by videsvau          #+#    #+#             */
/*   Updated: 2017/11/12 09:05:35 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

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
	if (sh->tty)
		tty_debug(sh, &sh->inpl->inp);
	ft_bzero(sh->buff, 6);
}
