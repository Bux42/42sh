/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   home_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 11:27:36 by videsvau          #+#    #+#             */
/*   Updated: 2018/02/05 21:27:57 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

void		home_end_shortcut(t_sh *sh, int len, int active)
{
	if (active == 1)
	{
		while (len > sh->width)
		{
			len -= sh->width;
			ft_putstr(tgetstr("do", NULL));
		}
		while (len--)
			custom_right(sh);
	}
	else
	{
		while (len > sh->width)
		{
			len -= sh->width;
			ft_putstr(tgetstr("up", NULL));
		}
		while (len--)
			custom_left(sh);
	}
}

void		home_end(t_sh *sh, t_inp **inp, int active)
{
	t_inp	*cp;
	int		len;

	len = 0;
	if ((cp = get_to_pos(inp)))
	{
		if (active == 1)
		{
			if (cp->pos == 2)
				custom_right(sh);
			cp->pos = 0;
			while (cp->next && (len++ > -1))
				cp = cp->next;
			home_end_shortcut(sh, len, active);
			cp->pos = 1;
		}
		else
		{
			if (cp->pos != 2)
				custom_left(sh);
			cp->pos = 0;
			while (cp->previous && (len++ > -1))
				cp = cp->previous;
			home_end_shortcut(sh, len, active);
			cp->pos = 2;
		}
	}
}
