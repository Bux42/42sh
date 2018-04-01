/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_history_forward.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 15:32:05 by videsvau          #+#    #+#             */
/*   Updated: 2018/04/01 22:31:04 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

int			check_empty_line(t_inp **inp)
{
	t_inp	*cp;
	int		letters;

	letters = 0;
	if ((cp = (*inp)))
	{
		while (cp)
		{
			if (cp->c > 31 && cp->c < 127)
				letters++;
			cp = cp->next;
		}
	}
	return (letters);
}

void		restore_history_from_file(t_sh *sh)
{
	char	*str;
	t_his	*tmp;

	sh->hist_res = 1;
	while (get_next_line(sh->fd, &str))
	{
		if (str)
		{
			if (!sh->history)
				sh->history = new_his(str);
			else
			{
				tmp = new_his(str);
				tmp->next = sh->history;
				sh->history->previous = tmp;
				sh->history = tmp;
			}
		}
		free(str);
	}
	sh->hist_res = 0;
}

void		clear_line(t_sh *sh, t_inp **inp)
{
	t_inp	*cp;
	int		dec;

	home_end(sh, inp, 0);
	if ((cp = (*inp)))
	{
		dec = 0;
		while (cp)
		{
			dec++;
			cp = cp->next;
		}
		print_spaces(dec, sh);
		while (dec--)
			custom_left(sh);
	}
}

void		clear_after_pos(t_sh *sh, t_inp **inp)
{
	t_inp	*cp;
	int		dec;

	if ((cp = get_to_pos(inp)))
	{
		dec = 0;
		while (cp)
		{
			dec++;
			cp = cp->next;
		}
		print_spaces(dec, sh);
		while (dec--)
			custom_left(sh);
	}
}

void		search_history_forward(t_sh *sh, t_his **history)
{
	if ((*history))
	{
		if ((*history)->previous)
		{
			clear_after_pos(sh, &sh->inpl->inp);
			if (sh->inpl->inp)
				free_list_from_beginning(&sh->inpl->inp);
			(*history) = (*history)->previous;
			search_history_inp(sh, &(*history)->inp);
		}
		else
		{
			clear_line(sh, &sh->inpl->inp);
			free_list_from_beginning(&sh->inpl->inp);
		}
	}
}
