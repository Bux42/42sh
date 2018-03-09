/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exclaim_misc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drecours <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 17:46:57 by drecours          #+#    #+#             */
/*   Updated: 2018/03/09 17:48:26 by drecours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "../../inc/header.h"

void	suppr_letter(t_inp **c)
{
	t_inp	*tmp;
	t_inp	*cp;

	tmp = *c;
	cp = NULL;
	if (tmp->next)
		cp = tmp->next;
	if (tmp->previous)
	{
		if (cp)
		{
			tmp->previous->next = cp;
			cp->previous = tmp->previous;
		}
		else
			tmp->previous->next = NULL;
	}
	if (cp && !tmp->previous)
		cp->previous = NULL;
	free(tmp);
	tmp = NULL;
}

t_inp	*insert_inp(t_inp **inp, char c)
{
	t_inp	*tmp;

	tmp = (*inp)->next;
	(*inp)->next = new_inp(c);
	(*inp)->next->previous = (*inp);
	(*inp)->next->next = tmp;
	if (tmp)
		tmp->previous = (*inp)->next;
	return ((*inp)->next);
}

void	suppr_exclaim(t_inp **inp, int i)
{
	while (--i >= 0)
		suppr_letter(&(*inp)->next);
	suppr_letter(&(*inp));
}

int		nothing_front_back(t_inp **input, int i)
{
	t_inp	*inp;

	inp = (*input);
	if (inp->previous)
		return (0);
	while (inp && inp->c && i--)
		inp = inp->next;
	if (!inp)
		return (-1);
	return (0);
}

void	pt_next(t_inp **input, int i)
{
	(*input) = (*input)->next;
	while (i-- > 0)
		(*input) = (*input)->next;
}
