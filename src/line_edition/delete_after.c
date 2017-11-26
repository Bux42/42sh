/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_after.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 07:29:44 by videsvau          #+#    #+#             */
/*   Updated: 2017/11/26 03:04:13 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

void		delete_first_letter(t_inp *cp, t_inp **inp)
{
	(*inp) = (*inp)->next;
	(*inp)->previous = NULL;
	(*inp)->pos = 2;
	free(cp);
}

void		delete_in_between(t_inp *cp)
{
	cp = cp->next;
	cp->previous->next = cp->next;
	if (cp->next)
		cp->next->previous = cp->previous;
	free(cp);
}

void		delete_after(t_sh *sh, t_inp **inp)
{
	t_inp	*cp;

	if ((cp = get_to_pos(inp)))
	{
		if (cp->next)
		{
			if (cp->pos == 2)
				delete_first_letter(cp, inp);
			else
				delete_in_between(cp);
			overwrite_deleted(sh, inp);
		}
		else if (cp->pos == 2)
		{
			print_spaces(1, sh);
			custom_left(sh);
			free(*inp);
			(*inp) = NULL;
		}
	}
}
