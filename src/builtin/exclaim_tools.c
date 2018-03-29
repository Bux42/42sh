/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exclaim_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drecours <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 12:25:32 by drecours          #+#    #+#             */
/*   Updated: 2018/03/29 15:03:15 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "../../inc/header.h"

int		no_history(void)
{
	ft_putstr_fd("!!: No history.", 2);
	custom_return();
	return (-1);
}

t_inp	*replace_double_exclaim(t_inp **his, t_inp **inp)
{
	t_inp	*insert;
	t_inp	*previous;

	previous = (*inp)->previous;
	insert = inp_dup(his);
	(*inp) = (*inp)->next->next;
	if (previous)
		previous->next = insert;
	insert->previous = previous;
	while (insert->next)
		insert = insert->next;
	if (*inp)
		(*inp)->previous = insert;
	insert->next = (*inp);
	return (insert);
}

int		last_command(t_sh *sh, t_inp **inp)
{
	if (!(sh->history))
		return (no_history());
	else
		*inp = replace_double_exclaim(&sh->history->inp, inp);
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

int		by_last(t_sh *sh, t_inp **inp, int pos)
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
	suppr_exclaim(&(*inp), i, sh);
	tmp = (!(sh->history && sh->history->inp)) ? (*inp)->next : tmp;
	suppr_letter(inp);
	*inp = tmp;
	return (0);
}
