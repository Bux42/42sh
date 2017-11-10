/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 15:22:15 by videsvau          #+#    #+#             */
/*   Updated: 2017/11/10 00:23:41 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

void		debug_file(t_inp **inp, t_sh *sh)
{
	int		fd;
	t_inp	*cp;

	if (*inp)
	{
		if ((fd = open("./debug.txt", O_WRONLY)) > -1)
		{
			cp = (*inp);
			ft_putchar_fd('\n', fd);
			while (cp)
			{
				ft_putchar_fd(cp->c, fd);
				ft_putchar_fd(' ', fd);
				cp = cp->next;
			}
			ft_putchar_fd('\n', fd);
			cp = (*inp);
			while (cp)
			{
				ft_putnbr_fd(cp->pos, fd);
				ft_putchar_fd(' ', fd);
				cp = cp->next;
			}
			ft_putchar_fd('\n', fd);
			ft_putnbr_fd(sh->width, fd);
			ft_putchar_fd('\t', fd);
			ft_putnbr_fd(sh->posy, fd);
			ft_putchar_fd('\t', fd);
			ft_putnbr_fd(sh->pos_at, fd);
			ft_putchar_fd('\n', fd);
			close(fd);
		}
	}
}
