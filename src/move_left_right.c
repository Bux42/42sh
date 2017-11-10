/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_left_right.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 18:39:04 by videsvau          #+#    #+#             */
/*   Updated: 2017/11/10 03:45:43 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

void		move_left(t_inp **inp, t_sh *sh)
{
	t_inp	*cp;

	if ((cp = (*inp)))
	{
		while (cp)
		{
			if (cp->pos == 1)
			{
				ft_putstr(tgetstr("le", NULL));
				if (sh->posy == 0)
					sh->posy = sh->width;
				else
					sh->posy--;
				if (!cp->previous)
					cp->pos = 2;
				else
				{
					cp->previous->pos = 1;
					cp->pos = 0;
				}
				return ;
			}
			cp = cp->next;
		}
	}
}

void		move_right(t_inp **inp, t_sh *sh)
{
	t_inp	*cp;

	if ((cp = (*inp)))
	{
		while (cp->next)
		{
			if (cp->pos)
			{
				if (sh->posy == sh->width)
				{
					ft_putstr(tgetstr("do", NULL));
					ft_putstr(tgetstr("cr", NULL));
					sh->posy = 0;
				}
				else
				{
					ft_putstr(tgetstr("nd", NULL));
					sh->posy++;
				}
				if (cp->pos == 1)
				{
					cp->pos = 0;
					cp->next->pos = 1;
				}
				else
					cp->pos = 1;
				return ;
			}
			cp = cp->next;
		}
		if (cp->pos == 2)
			cp->pos = 1;
	}
}
