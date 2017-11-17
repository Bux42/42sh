/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jump_up_down.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 09:56:22 by videsvau          #+#    #+#             */
/*   Updated: 2017/11/15 13:30:05 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

void		jump_up(t_sh *sh, t_inp **inp)
{
	t_inp	*cp;
	int		dec;

	if ((cp = get_to_pos(inp)))
	{
		if ((sh->pos_at - sh->width) > sh->prompt_len - 1)
		{
			dec = sh->width;
			cp->pos = 0;
			while (dec--)
			{
				custom_left(sh);
				if (cp->previous)
					cp = cp->previous;
				else
				{
					cp->pos = 2;
					break ;
				}
			}
			if (cp->pos != 2)
				cp->pos = 1;
		}
	}
}

int			inp_list_len(t_inp **inp)
{
	t_inp	*cp;
	int		i;

	if ((cp = (*inp)))
	{
		i = 0;
		while (cp)
		{
			i++;
			cp = cp->next;
		}
		return (i);
	}
	return (0);
}

void		jump_down(t_sh *sh, t_inp **inp)
{
	t_inp	*cp;
	int		dec;

	if ((cp = get_to_pos(inp)))
	{
		dec = sh->width;
		if (cp->pos == 2)
			custom_right(sh);
		cp->pos = 0;
		while (dec--)
		{
			if (cp->next && custom_right(sh))
				cp = cp->next;
			else
				break ;
		}
		cp->pos = 1;
		sh->pos_at = pos_at(inp, sh->prompt_len);
	}
}
