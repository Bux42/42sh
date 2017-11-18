/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_history_forward.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 15:32:05 by videsvau          #+#    #+#             */
/*   Updated: 2017/11/18 17:01:46 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

void		free_list_clear_line(t_sh *sh, t_inp **inp)
{
	t_inp	*cp;
	int		dec;
	int		decp;

	if ((cp = get_to_pos(inp)))
	{
		dec = 0;
		while (cp)
		{
			dec++;
			custom_left(sh);
			cp = cp->previous;
		}
		decp = dec;
		while (dec--)
		{
			ft_putchar(' ');
			check_endline(sh);
		}
		while (decp--)
			custom_left(sh);
	}
}

void		search_history_forward(t_sh *sh, t_his **history)
{
	if ((*history))
	{
		if ((*history)->previous)
		{
			if (sh->inpl->inp)
				free_list_from_beginning(&sh->inpl->inp);
			(*history) = (*history)->previous;
			search_history_inp(sh, &(*history)->inp);
		}
		else
		{
			free_list_clear_line(sh, &sh->inpl->inp);
			free_list_from_beginning(&sh->inpl->inp);
		}
	}
}
