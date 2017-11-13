/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_after.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 07:29:44 by videsvau          #+#    #+#             */
/*   Updated: 2017/11/13 07:48:12 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

void		delete_after(t_sh *sh, t_inp **inp)
{
	t_inp	*cp;

	if ((cp = get_to_pos(inp)))
	{
		if (cp->next)
		{
			cp = cp->next;
			cp->previous->next = cp->next;
			if (cp->next)
				cp->next->previous = cp->previous;
			free(cp);
			sh->posy = sh->posy;
			overwrite_deleted(sh, inp);
		}
		else if (cp->pos == 2)
		{
			ft_putchar(' ');
			check_endline(sh);
			custom_left(sh);
			free(*inp);
			(*inp) = NULL;
		}
	}
}
