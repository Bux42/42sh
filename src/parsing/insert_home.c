/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_home.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drecours <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 11:21:15 by drecours          #+#    #+#             */
/*   Updated: 2018/03/28 15:30:07 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

int		can_insert_home(t_inp **inp)
{
	if ((*inp)->previous && !ending_char((*inp)->previous->c))
		return (0);
	if ((*inp)->next)
	{
		if ((*inp)->next->c == '/')
			return (1);
		if (!ending_char((*inp)->next->c))
			return (0);
	}
	return (1);
}

void	try_insert_home(t_inp **inp, t_sh *sh)
{
	char	*variable;
	t_inp	*before;
	t_inp	*after;
	t_inp	*new;
	int		i;

	i = -1;
	if (can_insert_home(inp))
	{
		if ((variable = get_specific_env("HOME=", &sh->env)))
		{
			before = (*inp)->previous;
			after = (*inp)->next;
			free(*inp);
			new = NULL;
			while (variable[++i])
				inp_insert_posat(&new, variable[i]);
			if (before)
				before->next = new;
			new->previous = before;
			while (new->next)
				new = new->next;
			if (after)
				after->previous = new;
			new->next = after;
			*inp = new;
			free(variable);
		}
	}
}
