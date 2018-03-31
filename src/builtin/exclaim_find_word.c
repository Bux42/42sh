/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exclaim_find_word.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 20:56:04 by videsvau          #+#    #+#             */
/*   Updated: 2018/03/30 23:25:08 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./builtin.h"
#include "../../inc/header.h"

int		inp_contains_inp(t_inp **inp, t_inp **to_search)
{
	t_inp	*cp;
	t_inp	*search;

	if ((cp = (*inp)))
	{
		search = *to_search;
		while (cp)
		{
			while (cp && cp->c == search->c)
			{
				if (!search->next)
					return (1);
				else
					search = search->next;
				if (!cp->next)
					break ;
				else
					cp = cp->next;
			}
			search = *to_search;
			cp = cp->next;
		}
	}
	return (0);
}

t_inp	*find_everywhere(t_his **his, t_inp **inp)
{
	t_his	*cp;
	t_inp	*ret;
	t_inp	*to_search;

	ret = NULL;
	to_search = NULL;
	if ((cp = (*his)))
	{
		if ((to_search = get_search(inp)))
		{
			while (cp)
			{
				if (inp_contains_inp(&cp->inp, &to_search))
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

int		get_by_name(t_inp **inp, t_sh *sh)
{
	t_inp	*find;

	if (!(*inp)->next || ending_char((*inp)->next->c))
	{
		if (sh->history && sh->history->inp)
		{
			find = inp_dup(&sh->history->inp);
			(*inp) = (*inp)->previous;
			*inp = replace_exclaim_inter(find, inp);
			return (1);
		}
	}
	else
	{
		if ((find = find_everywhere(&sh->history, &(*inp)->next)))
		{
			(*inp) = (*inp)->previous;
			*inp = replace_exclaim_inter(find, inp);
			return (1);
		}
	}
	return (-1);
}
