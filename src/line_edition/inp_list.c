/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inp_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 06:38:04 by videsvau          #+#    #+#             */
/*   Updated: 2017/11/16 14:23:09 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

t_inp		*new_inp(char c)
{
	t_inp	*ret;

if (!(ret = (t_inp*)malloc(sizeof(t_inp))))
		return (NULL);
	ret->next = NULL;
	ret->previous = NULL;
	ret->c = c;
	ret->pos = 0;
	return (ret);
}

void		insert_middle(t_inp *first, t_inp *tmp)
{
	first->next->previous = tmp;
	tmp->next = first->next;
	first->next = tmp;
	tmp->previous = first;
	tmp->pos = 1;
	first->pos = 0;
}

void		insert_first(t_inp *first, t_inp *tmp, t_inp **inp)
{
	first->pos = 0;
	tmp->pos = 1;
	tmp->next = first;
	first->previous = tmp;
	(*inp) = tmp;
}

void		insert_beginning(t_inp *first, t_inp *tmp)
{
	tmp->pos = 1;
	first->pos = 0;
	first->next = tmp;
	tmp->previous = first;
}

void		inp_insert_posat(t_inp **inp, char c)
{
	t_inp	*first;
	t_inp	*tmp;

	if (!(*inp) && ((*inp) = new_inp(c)))
		(*inp)->pos = 1;
	else
	{
		first = (*inp);
		while (first->next)
		{
			if (first->pos)
			{
				tmp = new_inp(c);
				if (first->pos == 1)
					insert_middle(first, tmp);
				else
					insert_first(first, tmp, inp);
				return ;
			}
			tmp = first;
			first = first->next;
		}
		insert_beginning(first, new_inp(c));
	}
}
