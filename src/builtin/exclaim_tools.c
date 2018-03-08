/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exclaim_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drecours <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 12:25:32 by drecours          #+#    #+#             */
/*   Updated: 2018/03/08 19:48:52 by drecours         ###   ########.fr       */
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

int		no_history(void)
{
		ft_putstr("!!: No history.");
		custom_return();
		return (-1);
}

int		last_command(t_inp **inp, t_sh *sh, t_inp **t)
{
	t_inp	*input;
	t_inp	*tmp;

	if (!(sh->history && sh->history->next))
	{
		if (!((*inp)->next->next) && !((*inp)->previous))
			return (no_history());
	}
	else
	{
		tmp = (*inp)->next;
		input = sh->history->inp;
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
	suppr_exclaim(&(*inp), 1);
	return (0);
}

t_inp	*get_start(t_inp **inp, int i)
{
	t_inp	*tmp;

	tmp = (*inp);
	while (--i >= 0)
		tmp = tmp->next;
	return (tmp);
}

int		nothing_front_back(t_inp **input)
{
	t_inp	*inp;

	inp = (*input);
	if (inp->previous)
		return (0);
	if (inp->next->c == '-')
		inp = inp->next->next;
	else
		inp = inp->next;
	while (inp && inp->c <= '9' && inp->c >= '0')
		inp = inp->next;
	if (!inp || (inp->c <= '9' && inp->c >= '0'))
		return (-1);
	return (0);
}

void	pt_next(t_inp **input, int pos)
{
	(*input) = (*input)->next;
	if (pos == 1)
		(*input) = (*input)->next;
	while (*input && (*input)->c <= '9' && (*input)->c >= '0')
		(*input) = (*input)->next;
}

int		by_last(t_inp **inp, t_sh *sh, t_inp **t, int pos)
{
	t_inp	*input;
	t_inp	*tmp;
	(void)t;
	int		i;

	i = 0;
	ft_putstr("ici");
	if (!(sh->history && sh->history->inp && sh->history->inp->c))
	{
		ft_putstr("coin");
		if (nothing_front_back(inp) == -1)
			return (no_history());
	}
	ft_putstr("je rentre");
	if ((pos == 1 && get_by_last((*inp)->next, sh, &input, &i) == -1)
			|| (pos == 2 && get_by_first((*inp)->next, sh, &input, &i)))
		return (-1);
	ft_putstr("Historique cherche");
	if (input && input->c)
	{
		tmp = get_start(&(*inp), i);
		while (input && input->c)
		{
			tmp = insert_inp(&tmp, input->c);
			input = input->next;
		}
	}
	if (nothing_front_back(inp))
		t = NULL;
	else if (!((*inp)->previous))
		pt_next(t, pos);
	suppr_exclaim(&(*inp), i);
	ft_putstr("je sors");
	return (0);
}
/*
int		by_first(t_inp **inp, t_sh *sh, t_inp **t)
{
	t_inp	*input;
	t_inp	*tmp;
	int		i;

	i = 0;
	if (!(sh->history && sh->history->next))
	{
		if (nothing_front_back(inp) == -1)
			return (no_history());
	}
	if (get_by_last((*inp)->next, sh, &input, &i) == -1)
		return (-1);
	if (sh->history && sh->history->next)
	{
		tmp = get_start(&(*inp), i);
		while (input)
		{
			tmp = insert_inp(&tmp, input->c);
			input = input->next;
		}
	}
	if (nothing_front_back(inp))
		t = NULL;
	else if (!((*inp)->previous))
		pt_next(t);
	suppr_exclaim(&(*inp), i);
	return (0);
}*/

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
