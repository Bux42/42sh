/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 03:52:19 by videsvau          #+#    #+#             */
/*   Updated: 2017/11/12 04:00:49 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

int			check_dimentions(t_sh *sh)
{
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
}
