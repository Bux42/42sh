/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_cursor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 08:17:30 by videsvau          #+#    #+#             */
/*   Updated: 2017/11/26 05:59:21 by videsvau         ###   ########.fr       */
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

	if ((cp = get_to_pos(inp)))
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
	}
}

void		move_right(t_sh *sh, t_inp **inp)
{
	t_inp	*cp;

	if ((cp = get_to_pos(inp)))
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
	}
}

void		move_cursor(t_sh *sh, t_inp **inp, char c)
{
	t_inp	*cp;

	erase_completion(sh, &sh->inpl->inp);
	if (c == 68)
		move_left(sh, &sh->inpl->inp);
	if (c == 67)
		move_right(sh, &sh->inpl->inp);
	if (c == 70)
		home_end(sh, &sh->inpl->inp, 1);
	if (c == 72)
		home_end(sh, &sh->inpl->inp, 0);
	if (c == 65)
		if (!(cp = get_to_pos(inp)) || !cp->next)
			search_history_backward(sh, &sh->history);
	if (c == 66)
		search_history_forward(sh, &sh->history);
}
