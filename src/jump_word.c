/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jump_left_word.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 17:25:12 by videsvau          #+#    #+#             */
/*   Updated: 2017/11/04 19:45:43 by videsvau         ###   ########.fr       */
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

int			condition_nd(void)
{
	ft_putstr(tgetstr("nd", NULL));
	return (1);
}

int			condition_le(void)
{
	ft_putstr(tgetstr("le", NULL));
	return (1);
}

void		jump_right_word(t_inp **inp)
{
	t_inp	*cp;

	if ((cp = (*inp)))
	{
		if (cp->pos == 2)
			condition_nd();
		while (cp)
		{
			if (cp->pos && !(cp->pos = 0))
				break ;
			cp = cp->next;
		}
		if (cp->next && condition_nd())
			cp = cp->next;
		if (is_space(cp->c))
			while (cp->next && is_space(cp->next->c) && condition_nd())
				cp = cp->next;
		if (!is_space(cp->c))
		{
			while (cp->next && !is_space(cp->next->c) && condition_nd())
				cp = cp->next;
			while (cp->next && is_space(cp->next->c) && condition_nd())
				cp = cp->next;
		}
		cp->pos = 1;
	}
}

void		jump_left_word(t_inp **inp)
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
		if (cp->previous)
			ft_putstr(tgetstr("le", NULL));
		if (cp->previous && !is_space(cp->c) && condition_le())
			cp = cp->previous;
		while (cp->previous && is_space(cp->c) && condition_le())
			cp = cp->previous;
		while (cp->previous && !is_space(cp->previous->c) && condition_le())
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
