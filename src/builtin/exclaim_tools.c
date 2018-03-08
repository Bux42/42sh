/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exclaim_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drecours <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 12:25:32 by drecours          #+#    #+#             */
/*   Updated: 2018/03/08 13:46:38 by drecours         ###   ########.fr       */
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

int		last_command(t_inp **inp, t_sh *sh, t_inp **t)
{
	t_inp	*input;
	t_inp	*tmp;

	if (!(sh->history && sh->history->next))
	{
		ft_putstr("!!: No history.");
		custom_return();
		if (!((*inp)->next->next) && !((*inp)->previous))
			return (-1);
	}
	else
	{
		tmp = (*inp)->next;
		input = sh->history->inp;
		//ft_putchar((*inp)->c);
		//ft_putchar((*inp)->next->c);
		while (input)
		{
			tmp = insert_inp(&tmp, input->c);
			input = input->next;
		}
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
