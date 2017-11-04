/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 15:22:15 by videsvau          #+#    #+#             */
/*   Updated: 2017/11/02 18:20:01 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

void		debug_file(t_inp **inp)
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
			close(fd);
		}
	}
}
