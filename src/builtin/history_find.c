/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_find.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drecours <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 14:40:55 by drecours          #+#    #+#             */
/*   Updated: 2018/03/30 21:39:19 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "../../inc/header.h"

t_inp	*find_from_start(t_his **his, int nb)
{
	t_inp	*ret;
	t_his	*cp;

	ret = NULL;
	if ((cp = (*his)))
	{
		while (cp->next)
			cp = cp->next;
		while (nb > 1 && cp)
		{
			cp = cp->previous;
			nb--;
		}
		if (cp && cp->inp)
			ret = inp_dup(&cp->inp);
	}
	return (ret);
}

int		get_by_first(t_inp **inp, t_sh *sh)
{
	int		nb;
	t_inp	*found;
	t_inp	*before;

	before = (*inp)->previous->previous;
	nb = inp_to_int(inp);
	if ((found = find_from_start(&sh->history, nb)))
	{
		if (before)
			before->next = *inp;
		free((*inp)->previous);
		(*inp)->previous = before;
		*inp = insert_found(inp, found);
		return (1);
	}
	return (-1);
}

int		inp_start_with_inp(t_inp **inp, t_inp **to_search)
{
	t_inp	*cp;
	t_inp	*search;

	if ((cp = (*inp)))
	{
		search = *to_search;
		while (cp && search && search->c == cp->c)
		{
			cp = cp->next;
			search = search->next;
		}
		if (!search)
			return (1);
	}
	return (0);
}

t_inp	*find_beginning(t_his **his, t_inp **inp)
{
	t_inp	*ret;
	t_inp	*to_search;
	t_his	*cp;

	ret = NULL;
	to_search = NULL;
	if ((cp = (*his)))
	{
		if ((to_search = get_search(inp)))
		{
			while (cp)
			{
				if (inp_start_with_inp(&cp->inp, &to_search))
					break ;
				cp = cp->next;
			}
			if (cp)
				ret = inp_dup(&cp->inp);
			free_list_from_beginning(&to_search);
		}
	}
	return (ret);
}

int		get_by_beg(t_inp **inp, t_sh *sh)
{
	t_inp	*find;

	if ((find = find_beginning(&sh->history, inp)))
	{
		(*inp) = (*inp)->previous;
		*inp = replace_exclaim_inter(find, inp);
		return (1);
	}
	return (-1);
}
