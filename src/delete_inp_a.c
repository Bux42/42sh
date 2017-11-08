/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_inp_a.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 16:24:53 by videsvau          #+#    #+#             */
/*   Updated: 2017/11/07 20:04:21 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

void		delete_last(t_inp **inp, t_inp *cp)
{
	(*inp) = NULL;
	free(*inp);
	free(cp);
}

void		delete_at_begining(t_inp **inp, t_inp *cp)
{
	(*inp) = (*inp)->next;
	(*inp)->previous = NULL;
	(*inp)->pos = 2;
	free(cp);
}

void		delete_middle(t_inp *cp)
{
	t_inp	*tmp;

	tmp = cp->next;
	if (tmp->next)
	{
		cp = tmp->next;
		cp->previous = tmp->previous;
		tmp->previous->next = cp;
	}
	else
		cp->next = NULL;
	free(tmp);
}

void		delete_pos_a(t_inp **inp)
{
	t_inp	*cp;

	if ((cp = (*inp)))
	{
		while (cp)
		{
			if (cp->pos)
			{
				if (cp->next)
				{
					if (cp->pos == 2)
						delete_at_begining(inp, cp);
					else
						delete_middle(cp);
				}
				else if (cp->pos == 2)
					delete_last(inp, cp);
				return ;
			}
			cp = cp->next;
		}
	}
}
