/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_quotes_tools.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 06:26:00 by videsvau          #+#    #+#             */
/*   Updated: 2018/04/08 06:49:39 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

void		rep_backslash(char c, t_inp **inp, t_inp **bef)
{
	t_inp	*aft;

	aft = NULL;
	if (c)
	{
		aft = (*inp)->next->next;
		(*inp)->c = c;
		(*inp)->next = aft;
		free((aft)->previous);
		(aft)->previous = (*inp);
	}
	else
	{
		(*inp) = (*inp)->next;
		free((*inp)->previous);
		if (*bef)
			(*bef)->next = (*inp);
		(*inp)->previous = *bef;
	}
}

void		get_previous_inp(t_inp **inp, t_inp **previous)
{
	*previous = (*inp)->previous;
	(*inp) = (*inp)->next;
	free((*inp)->previous);
	if (*previous)
		(*previous)->next = (*inp);
	(*inp)->previous = *previous;
}

void		relink_with_end(t_inp **inp)
{
	t_inp	*after;

	after = (*inp)->next;
	(*inp) = (*inp)->previous;
	if (after)
		after->previous = (*inp);
	free((*inp)->next);
	(*inp)->next = after;
}
