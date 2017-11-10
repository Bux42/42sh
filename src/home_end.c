/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   home_end.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 19:09:16 by videsvau          #+#    #+#             */
/*   Updated: 2017/11/10 06:09:13 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

void		home_end(t_inp **inp, int i, t_sh *sh)
{
	t_inp	*cp;

	if ((cp = (*inp)))
	{
		while (!cp->pos)
			cp = cp->next;
		if (cp->pos != 2 && i)
			padding_left(sh);
		if (cp->pos == 2 && !i)
			padding_right(sh);
		cp->pos = 0;
		if (i)
		{
			while (cp->previous && padding_left(sh))
				cp = cp->previous;
			cp->pos = 2;
		}
		else
		{
			while (cp->next && padding_right(sh))
				cp = cp->next;
			cp->pos = 1;
		}
	}
}
