/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimized_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 21:58:15 by videsvau          #+#    #+#             */
/*   Updated: 2018/02/08 22:34:56 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

int			print_inp(t_inp *cp, t_sh *sh)
{
	char	buff[sh->width + 1];
	int		i;
	int		written;

	i = -1;
	written = 0;
	ft_bzero(buff, sh->width + 1);
	while (cp->next && (written++ > -1))
	{
		buff[++i] = cp->next->c;
		if (sh->posy == sh->width)
		{
			ft_putstr(buff);
			ft_bzero(buff, sh->width + 1);
			i = -1;
			ft_putchar(' ');
			ft_putstr(tgetstr("le", NULL));
			sh->posy = 1;
		}
		else
			sh->posy++;
		cp = cp->next;
	}
	ft_putstr(buff);
	return (written);
}
