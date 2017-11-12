/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 03:52:19 by videsvau          #+#    #+#             */
/*   Updated: 2017/11/12 05:27:52 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

int			check_dimentions(t_sh *sh)
{
	if (sh->width + 1 == sh->posy)
		ft_putchar(' ');
	if (!(tgetent(NULL, TERM)))
		return (0);
	if (tgetnum("co") != sh->width)
		;
	else
		;
	return (1);
}

void		treat_input(t_sh *sh)
{
	if (check_dimentions(sh))
		sh->width = tgetnum("co");
	else
		return ;
	ft_putchar(sh->buff[0]);
	if (sh->posy == sh->width)
	{
		sh->posy = 1;
		ft_putchar(' ');
		ft_putstr(tgetstr("le", NULL));
	}
	else
		sh->posy++;
	if (sh->tty)
		tty_debug(sh);
}
