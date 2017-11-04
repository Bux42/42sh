/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   home_end.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 19:09:16 by videsvau          #+#    #+#             */
/*   Updated: 2017/11/04 20:20:26 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

void		home_end(t_inp **inp, int i)
{
	t_inp	*cp;

	if ((cp = (*inp)))
	{
		while (!cp->pos)
			cp = cp->next;
		if (cp->pos == 2 && !i)
			condition_nd();
		else if (i)
			condition_le();
		cp->pos = 0;
		if (i)
		{
			while (cp->previous && condition_le())
				cp = cp->previous;
			cp->pos = 2;
		}
		else
		{
			while (cp->next && condition_nd())
				cp = cp->next;
			cp->pos = 1;
		}
	}
}
