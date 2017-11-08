/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_inp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 15:38:14 by videsvau          #+#    #+#             */
/*   Updated: 2017/11/07 20:03:26 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

void		remove_first(t_inp *cp, t_inp **inp)
{
	t_inp	*tmp;

	if (cp->next)
	{
		tmp = (*inp);
		(*inp) = (*inp)->next;
		(*inp)->previous = NULL;
		(*inp)->pos = 2;
		free(tmp);
	}
	else
	{
		(*inp) = NULL;
		free(*inp);
		free(cp);
	}
}

void		remove_middle(t_inp *cp)
{
	t_inp	*tmp;

	if (cp->next)
	{
		tmp = cp->previous;
		tmp->next = cp->next;
		tmp->next->previous = tmp;
		tmp->pos = 1;
		free(cp);
	}
	else
	{
		tmp = cp;
		cp = cp->previous;
		cp->next = NULL;
		cp->pos = 1;
		free(tmp);
	}
}

void		delete_pos(t_inp **inp)
{
	t_inp	*cp;

	if (*inp)
	{
		cp = (*inp);
		while (cp)
		{
			if (cp->pos == 1)
			{
				if (!cp->previous)
					remove_first(cp, inp);
				else
					remove_middle(cp);
				return ;
			}
			cp = cp->next;
		}
	}
}
