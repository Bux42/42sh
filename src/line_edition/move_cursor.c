/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_cursor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 08:17:30 by videsvau          #+#    #+#             */
/*   Updated: 2017/11/12 12:36:57 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

int			custom_left(t_sh *sh)
{
	if (sh->posy == 1)
		sh->posy = sh->width;
	else
		sh->posy--;
	ft_putstr(tgetstr("le", NULL));
	return (1);
}

int			custom_right(t_sh *sh)
{
	if (sh->posy == sh->width)
	{
		sh->posy = 1;
		ft_putstr(tgetstr("do", NULL));
		ft_putstr(tgetstr("cr", NULL));
	}
	else
	{
		ft_putstr(tgetstr("nd", NULL));
		sh->posy++;
	}
	return (1);
}

void		move_left(t_sh *sh, t_inp **inp)
{
	t_inp	*cp;

	if ((cp = (*inp)))
	{
		while (cp)
		{
			if (cp->pos)
			{
				if (cp->pos == 1)
				{
					if (cp->previous)
					{
						cp->pos = 0;
						cp->previous->pos = 1;
					}
					else
						cp->pos = 2;
					custom_left(sh);
				}
				break;
			}
			cp = cp->next;
		}
	}
}

void		move_right(t_sh *sh, t_inp **inp)
{
	t_inp	*cp;

	if ((cp = (*inp)))
	{
		while (cp)
		{
			if (cp->pos)
			{
				if (cp->pos == 2)
				{
					cp->pos = 1;
					custom_right(sh);
				}
				else
				{
					if (cp->next)
					{
						cp->pos = 0;
						cp->next->pos = 1;
						custom_right(sh);
					}
				}
				break ;
			}
			cp = cp->next;
		}
	}
}

void		move_cursor(t_sh *sh, char c)
{
	if (c == 68)
		move_left(sh, &sh->inpl->inp);
	if (c == 67)
		move_right(sh, &sh->inpl->inp);
	if (c == 70)
		home_end(sh, &sh->inpl->inp, 1);
	if (c == 72)
		home_end(sh, &sh->inpl->inp, 0);
}
