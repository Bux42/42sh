/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exclaim_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drecours <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 12:25:32 by drecours          #+#    #+#             */
/*   Updated: 2018/03/09 17:50:16 by drecours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "../../inc/header.h"

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

int		get_his(t_inp **inp, t_sh *sh, t_inp **input, int pos)
{
	if (pos == 1)
		return (get_by_last((*inp)->next, sh, input));
	if (pos == 2)
		return (get_by_first((*inp)->next, sh, input));
	if (pos == 3)
		return (get_by_beg((*inp)->next, sh, input));
	if (pos == 4)
		return (get_by_name((*inp)->next, sh, input));
	return (-1);
}

int		by_last(t_inp **inp, t_sh *sh, t_inp **t, int pos)
{
	t_inp	*input;
	t_inp	*tmp;
	int		i;

	i = 0;
	if ((i = get_his(inp, sh, &input, pos)) == -1)
		return (-1);
	if (!(sh->history && sh->history->inp && sh->history->inp->c))
		if (nothing_front_back(inp, i) == -1)
			return (no_history());
	if (input && input->c)
	{
		tmp = get_start(&(*inp), i);
		while (input && input->c)
		{
			tmp = insert_inp(&tmp, input->c);
			input = input->next;
		}
	}
	if (nothing_front_back(inp, i))
		t = NULL;
	else if (!((*inp)->previous))
		pt_next(t, i);
	suppr_exclaim(&(*inp), i);
	return (0);
}
