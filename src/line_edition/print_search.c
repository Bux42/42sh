/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_search.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 04:53:11 by videsvau          #+#    #+#             */
/*   Updated: 2018/01/27 06:25:23 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

void		print_match(t_sh *sh)
{
	int		i;

	i = 0;
	while (i++ < 3)
		custom_right(sh);
	while (sh->search_pos->inp->previous)
		sh->search_pos->inp = sh->search_pos->inp->previous;
	while (sh->search_pos->inp)
	{
		ft_putchar(sh->search_pos->inp->c);
		check_endline(sh);
		if (sh->search_pos->inp->next)
			sh->search_pos->inp = sh->search_pos->inp->next;
		else
			break ;
	}
	while (sh->search_pos->inp->previous)
	{
		sh->search_pos->inp = sh->search_pos->inp->previous;
		custom_left(sh);
	}
	i = 0;
	while (i++ < 4)
		custom_left(sh);
	sh->failed_search = 0;
}

int			init_search(t_sh *sh, int repeat, t_his **his)
{
	sh->failed_search = 1;
	if (repeat || !sh->search_pos)
		sh->search_pos = (*his);
	else if (sh->search == 2 && sh->search_pos->previous)
		sh->search_pos = sh->search_pos->previous;
	else if (sh->search == 1 && sh->search_pos->next)
		sh->search_pos = sh->search_pos->next;
	else
		return (0);
	if (!sh->his_search)
		return (0);
	return (1);
}

int			found_match(t_inp *cp, t_inp **search_pos)
{
	t_inp	*pos;

	if ((pos = (*search_pos)))
	{
		while (pos)
		{
			while (pos && cp->c == pos->c)
			{
				if (!cp->next)
					return (1);
				cp = cp->next;
				pos = pos->next;
			}
			if (pos)
				pos = pos->next;
		}
	}
	return (0);
}

void		print_search_forward(t_sh *sh, t_inp **search, t_his **his, int re)
{
	t_inp	*cp;

	if (!init_search(sh, re, his))
		return ;
	cp = *search;
	while (sh->search_pos)
	{
		if (found_match(cp, &sh->search_pos->inp))
			return ((void)print_match(sh));
		while (sh->search_pos->inp->previous)
			sh->search_pos->inp = sh->search_pos->inp->previous;
		cp = (*search);
		if (sh->search_pos->previous)
			sh->search_pos = sh->search_pos->previous;
		else
			break ;
	}
}

void		print_search_backward(t_sh *sh, t_inp **search, t_his **his, int re)
{
	t_inp	*cp;

	if (!init_search(sh, re, his))
		return ;
	cp = *search;
	while (sh->search_pos)
	{
		if (found_match(cp, &sh->search_pos->inp))
			return ((void)print_match(sh));
		while (sh->search_pos->inp->previous)
			sh->search_pos->inp = sh->search_pos->inp->previous;
		cp = (*search);
		if (sh->search_pos->next)
			sh->search_pos = sh->search_pos->next;
		else
			break ;
	}
}
