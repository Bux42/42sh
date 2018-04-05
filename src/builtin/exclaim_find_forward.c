/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exclaim_find_forward.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 21:10:20 by videsvau          #+#    #+#             */
/*   Updated: 2018/03/30 21:10:41 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./builtin.h"
#include "../../inc/header.h"

t_inp	*find_backward_search(t_his **his, int nb)
{
	t_inp	*ret;
	t_his	*cp;

	ret = NULL;
	if ((cp = (*his)))
	{
		while (nb > 1 && cp)
		{
			nb--;
			cp = cp->next;
		}
		if (cp && cp->inp)
			ret = inp_dup(&cp->inp);
	}
	return (ret);
}

t_inp	*replace_exclaim_inter(t_inp *found, t_inp **inp)
{
	t_inp	*previous;
	t_inp	*tmp;

	previous = (*inp)->previous;
	while ((*inp) && !ending_char((*inp)->c))
	{
		tmp = *inp;
		(*inp) = (*inp)->next;
		free(tmp);
	}
	if (previous)
		previous->next = found;
	found->previous = previous;
	while (found->next)
		found = found->next;
	found->next = (*inp);
	if (*inp)
		(*inp)->previous = found;
	return (found);
}

t_inp	*insert_found(t_inp **inp, t_inp *found)
{
	t_inp	*before;
	t_inp	*tmp;

	before = (*inp)->previous;
	while ((*inp) && (*inp)->c > 47 && (*inp)->c < 58)
	{
		tmp = *inp;
		(*inp) = (*inp)->next;
		free(tmp);
	}
	found->previous = before;
	if (before)
		before->next = found;
	while (found->next)
		found = found->next;
	if (*inp)
		(*inp)->previous = found;
	found->next = *inp;
	if (!*inp)
		return (found);
	return (*inp);
}

void	free_last_two(t_inp **inp)
{
	t_inp	*before;

	before = (*inp)->previous->previous->previous;
	free((*inp)->previous->previous);
	free((*inp)->previous);
	(*inp)->previous = before;
	if (before)
		before->next = (*inp);
}

int		get_by_last(t_inp **inp, t_sh *sh)
{
	int		nb;
	t_inp	*found;

	if ((*inp)->c > 48 && (*inp)->c < 58)
	{
		nb = inp_to_int(inp);
		if ((found = find_backward_search(&sh->history, nb)))
		{
			free_last_two(inp);
			*inp = insert_found(inp, found);
			return (1);
		}
	}
	return (-1);
}
