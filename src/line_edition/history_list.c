/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 14:06:27 by videsvau          #+#    #+#             */
/*   Updated: 2017/11/17 16:17:05 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

int			history_len(t_his **history)
{
	int		i;
	t_his	*cp;

	i = 0;
	if ((cp = (*history)))
	{
		while (cp)
		{
			i++;
			cp = cp->next;
		}
	}
	return (i);
}

t_his		*history_new(t_inp *inp)
{
	t_his	*ret;
	t_inp	*cp;

	cp = NULL;
	if (!(ret = (t_his*)malloc(sizeof(t_his))))
		return (NULL);
	while (inp)
	{
		inp_insert_posat(&cp, inp->c);
		inp = inp->next;
	}
	ret->next = NULL;
	ret->previous = NULL;
	ret->inp = cp;
	return (ret);
}

void		history_push_front(t_his **history, t_inp *inp)
{
	t_his	*first;

	if (!(*history))
		(*history) = history_new(inp);
	else
	{
		first = history_new(inp);
		while ((*history)->previous)
			(*history) = (*history)->previous;
		(*history)->previous = first;
		first->next = (*history);
		(*history) = first;
	}
}

void		search_history_inp(t_sh *sh, t_inp **inp)
{
	t_inp	*cp;
	int		dec;
	int		diff;

	dec = 0;
	if ((cp = (*inp)))
	{
		diff = sh->posy - sh->prompt_len;
		while (sh->posy > sh->prompt_len)
		{
			custom_left(sh);
			dec++;
		}
		while (cp)
		{
			ft_putchar(cp->c);
			check_endline(sh);
			inp_insert_posat(&sh->inpl->inp, cp->c);
			cp = cp->next;
			dec--;
			diff--;
		}
		while (dec-- > 0)
		{
			ft_putchar(' ');
			check_endline(sh);
		}
		while (diff-- > 0)
			custom_left(sh);
	}
}

void		search_history_backward(t_sh *sh, t_his **history)
{
	if ((*history))
	{
		if ((*history)->next)
			(*history) = (*history)->next;
		free_list_from_beginning(&sh->inpl->inp);
		search_history_inp(sh, &(*history)->inp);
	}
}
