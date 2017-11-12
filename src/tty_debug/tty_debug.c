/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tty_debug.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 05:07:52 by videsvau          #+#    #+#             */
/*   Updated: 2017/11/12 05:26:39 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

void		tty_debug(t_sh *sh)
{
	char	buff[2048];

	ft_bzero(buff, 2047);
	ft_strcat(buff, "echo ");
	ft_strcat(buff, " posy ");
	ft_strcat(buff, ft_itoa(sh->posy));
	ft_strcat(buff, "     width ");
	ft_strcat(buff, ft_itoa(sh->width));
	ft_strcat(buff, " > ");
	ft_strcat(buff, sh->tty);
	system(buff);
}

int			get_tty(t_sh *sh, char *av)
{
	if (av)
		sh->tty = ft_strdup(av);
	else
		sh->tty = NULL;
	return (1);
}
