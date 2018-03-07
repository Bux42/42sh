/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exclaim_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drecours <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 12:25:32 by drecours          #+#    #+#             */
/*   Updated: 2018/03/07 18:08:55 by drecours         ###   ########.fr       */
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

int		last_command(t_inp **inp, t_sh *sh, t_inp **t)
{
	t_inp	*input;

	if (!(sh->history && sh->history->next))
	{
		ft_putstr("!!: No history.");
		custom_return();
		return (-1);
	}
	input = sh->history->inp;
	while (input)
	{
		inp_insert_posat(inp, input->c);
		input = input->next;
	}
	if (!(*inp)->previous && (*inp)->next->next)
		*t = (*inp)->next->next;
	else if (!(*inp)->previous)
		t = NULL;
	suppr_letter(&(*inp)->next);
	suppr_letter(&(*inp));
	return (0);
}

int		by_last(t_inp **inp, t_sh *sh)
{
	(void)inp;
	t_inp	*c;

	c = sh->history->inp;
	ft_putchar('b');
	return (0);
}

int		by_first(t_inp **inp, t_sh *sh)
{
	(void)inp;
	t_inp	*c;

	c = sh->history->inp;
	ft_putchar('c');
	return (0);
}

int		search_that(t_inp **inp, t_sh *sh)
{
	(void)inp;
	t_inp	*c;

	c = sh->history->inp;
	ft_putchar('d');

	return (0);
}

int		search(t_inp **inp, t_sh *sh)
{
	(void)inp;
	t_inp	*c;

	c = sh->history->inp;
	//ft_putchar('e');
	return (0);
}
