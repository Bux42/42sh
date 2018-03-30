/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exclaim_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drecours <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 12:25:32 by drecours          #+#    #+#             */
/*   Updated: 2018/03/30 20:47:08 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "../../inc/header.h"

t_inp	*get_search(t_inp **inp)
{
	t_inp	*ret;
	t_inp	*cp;

	ret = NULL;
	if ((cp = (*inp)))
	{
		while (cp && !ending_char(cp->c))
		{
			inp_insert_posat(&ret, cp->c);
			cp = cp->next;
		}
	}
	return (ret);
}

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
	t_inp	*tmp;

	previous = (*inp)->previous;
	insert = inp_dup(his);
	tmp = *inp;
	(*inp) = (*inp)->next;
	free(tmp);
	tmp = *inp;
	(*inp) = (*inp)->next;
	free(tmp);
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
	if (!(sh->history) || !sh->history->inp)
		return (no_history());
	else
		*inp = replace_double_exclaim(&sh->history->inp, inp);
	return (0);
}

int		get_his(t_sh *sh, t_inp **inp, int pos)
{
	if ((*inp)->next)
	{
		(*inp) = (*inp)->next;
		if (pos == 1)
			(*inp) = (*inp)->next;
		if (pos == 1 && (*inp))
			return (get_by_last(inp, sh));
		if (pos == 2)
			return (get_by_first(inp, sh));
		if (pos == 4)
			return (get_by_name(inp, sh));
		if (pos == 3)
			return (get_by_beg(inp, sh));
	}
	return (-1);
}
