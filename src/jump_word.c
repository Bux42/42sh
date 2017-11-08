/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jump_left_word.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 17:25:12 by videsvau          #+#    #+#             */
/*   Updated: 2017/11/07 20:02:20 by videsvau         ###   ########.fr       */
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

void		jump_right_word(t_inp **inp)
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
		if (cp->next)
			cp = cp->next;
		if (is_space(cp->c))
			while (cp->next && is_space(cp->next->c))
				cp = cp->next;
		if (!is_space(cp->c))
		{
			while (cp->next && !is_space(cp->next->c))
				cp = cp->next;
			while (cp->next && is_space(cp->next->c))
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
		if (cp->previous && !is_space(cp->c))
			cp = cp->previous;
		while (cp->previous && is_space(cp->c))
			cp = cp->previous;
		while (cp->previous && !is_space(cp->previous->c))
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
