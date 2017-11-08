/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   home_end.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 19:09:16 by videsvau          #+#    #+#             */
/*   Updated: 2017/11/07 20:02:08 by videsvau         ###   ########.fr       */
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
		cp->pos = 0;
		if (i)
		{
			while (cp->previous)
				cp = cp->previous;
			cp->pos = 2;
		}
		else
		{
			while (cp->next)
				cp = cp->next;
			cp->pos = 1;
		}
	}
}
