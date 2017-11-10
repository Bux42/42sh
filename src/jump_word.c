/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jump_left_word.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 17:25:12 by videsvau          #+#    #+#             */
/*   Updated: 2017/11/10 06:12:05 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

int			is_space(char c)
{
	if (c == ' ')
		return (1);
	if (c == '\t')
		return (1);
	if (c == '\n')
		return (1);
	if (c == '\'')
		return (1);
	if (c == '\"')
		return (1);
	return (0);
}

int			padding_right(t_sh *sh)
{
	if (sh->posy == sh->width)
	{
		ft_putstr(tgetstr("do", NULL));
		ft_putstr(tgetstr("cr", NULL));
		sh->posy = 0;
	}
	else
	{
		ft_putstr(tgetstr("nd", NULL));
		sh->posy++;
	}
	return (1);
}

int			padding_left(t_sh *sh)
{
	if (sh->posy == 0)
		sh->posy = sh->width;
	else
		sh->posy--;
	ft_putstr(tgetstr("le", NULL));
	return (1);
}

void		jump_right_word(t_inp **inp, t_sh *sh)
{
	t_inp	*cp;

	if ((cp = (*inp)))
	{
		while (cp)
		{
			if (cp->pos == 2)
				padding_right(sh);
			if (cp->pos && !(cp->pos = 0))
				break ;
			cp = cp->next;
		}
		if (cp->next && padding_right(sh))
			cp = cp->next;
		if (is_space(cp->c))
			while (cp->next && is_space(cp->next->c) && padding_right(sh))
				cp = cp->next;
		if (!is_space(cp->c))
		{
			while (cp->next && !is_space(cp->next->c) && padding_right(sh))
				cp = cp->next;
			while (cp->next && is_space(cp->next->c) && padding_right(sh))
				cp = cp->next;
		}
		cp->pos = 1;
	}
}

void		jump_left_word(t_inp **inp, t_sh *sh)
{
	t_inp	*cp;

	if ((cp = (*inp)))
	{
		while (cp)
		{
			if (cp->pos && !(cp->pos = 0))
				break ;
			cp = cp->next;
		}
		if (cp->previous && cp->previous->previous)
			padding_left(sh);
		if (cp->previous && !is_space(cp->c) && padding_left(sh))
			cp = cp->previous;
		while (cp->previous && is_space(cp->c) && padding_left(sh))
			cp = cp->previous;
		while (cp->previous && !is_space(cp->previous->c) && padding_left(sh))
			cp = cp->previous;
		if (!cp->previous)
			cp->pos = 2;
		else
		{
			cp = cp->previous;
			cp->pos = 1;
		}
	}
}
