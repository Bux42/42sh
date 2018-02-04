/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 14:06:27 by videsvau          #+#    #+#             */
/*   Updated: 2018/02/04 18:37:35 by videsvau         ###   ########.fr       */
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

t_his		*history_new(t_inp *inp, t_sh *sh)
{
	t_his	*ret;
	t_inp	*cp;

	cp = NULL;
	if (!(ret = (t_his*)malloc(sizeof(t_his))))
		return (NULL);
	while (inp)
	{
		if (inp->c != '\n')
		{
			if (!sh->hist_res)
				write(sh->fd, &inp->c, 1);
			inp_insert_posat(&cp, inp->c);
		}
		if (inp->next)
			inp = inp->next;
		else
			break ;
	}
	if (!sh->hist_res)
		write(sh->fd, "\n", 1);
	while (inp->previous)
		inp = inp->previous;
	ret->next = NULL;
	ret->previous = NULL;
	ret->inp = cp;
	return (ret);
}

void		history_push_front(t_his **history, t_inp *inp, t_sh *sh)
{
	t_his	*first;

	if (!(*history))
		(*history) = history_new(inp, sh);
	else
	{
		first = history_new(inp, sh);
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
		home_end(sh, &sh->inpl->inp, 1);
		diff = sh->pos_at - sh->prompt_len;
		while (sh->pos_at-- > sh->prompt_len && (dec++) > -1)
			custom_left(sh);
		while (cp)
		{
			ft_putchar(cp->c);
			check_endline(sh);
			inp_insert_posat(&sh->inpl->inp, cp->c);
			cp = cp->next;
			dec--;
			diff--;
		}
		print_spaces(dec, sh);
		while (diff-- > 0)
			custom_left(sh);
	}
}

void		search_history_backward(t_sh *sh, t_his **history)
{
	if ((*history))
	{
		if (sh->inpl->inp)
		{
			free_list_from_beginning(&sh->inpl->inp);
			if ((*history)->next)
				(*history) = (*history)->next;
		}
		search_history_inp(sh, &(*history)->inp);
	}
}
