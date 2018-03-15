/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jump_words.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 09:55:17 by videsvau          #+#    #+#             */
/*   Updated: 2018/03/16 00:04:00 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

t_inp		*get_to_pos(t_inp **inp)
{
	t_inp	*cp;

	if ((cp = (*inp)))
	{
		while (cp)
		{
			if (cp->pos)
				return (cp);
			cp = cp->next;
		}
	}
	return (NULL);
}

int			is_space(char c)
{
	if (c == ' ')
		return (1);
	if (c == '\t')
		return (1);
	if (c == '\n')
		return (1);
	return (0);
}

void		jump_left(t_sh *sh, t_inp **inp)
{
	t_inp	*cp;
	int		dec;

	dec = 1;
	if ((cp = get_to_pos(inp)))
	{
		if (cp->pos == 1 && !cp->previous && (cp->pos = 2))
			custom_left(sh);
		else if (cp->pos != 2)
		{
			cp->pos = 0;
			cp = cp->previous;
			while (is_space(cp->c) && cp->previous && dec++)
				cp = cp->previous;
			while (!is_space(cp->c) && cp->previous && dec++)
				cp = cp->previous;
			restore_cursor_pos(dec, sh);
			if (cp->previous)
				cp->pos = 1;
			else if (custom_left(sh))
				cp->pos = 2;
		}
	}
}

void		jump_right(t_sh *sh, t_inp **inp)
{
	t_inp	*cp;
	int		dec;

	dec = 1;
	if ((cp = get_to_pos(inp)))
	{
		if (cp->pos == 2 && custom_right(sh))
			cp->pos = 1;
		if (cp->next)
		{
			cp->pos = 0;
			while (cp->next && !is_space(cp->next->c) && dec++)
				cp = cp->next;
			while (cp->next && is_space(cp->next->c) && dec++)
				cp = cp->next;
			restore_cursor_right(dec - 1, sh);
			cp->pos = 1;
		}
	}
}

void		jump_words(t_sh *sh, char c)
{
	erase_completion(sh, &sh->inpl->inp);
	if (c == 65)
		jump_up(sh, &sh->inpl->inp);
	if (c == 66)
		jump_down(sh, &sh->inpl->inp);
	if (c == 67)
		jump_right(sh, &sh->inpl->inp);
	if (c == 68)
		jump_left(sh, &sh->inpl->inp);
}
