/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_history_forward.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 15:32:05 by videsvau          #+#    #+#             */
/*   Updated: 2017/11/19 17:03:23 by videsvau         ###   ########.fr       */
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
			if (cp->c > 32 && cp->c < 127)
				letters++;
			cp = cp->next;
		}
	}
	return (letters);
}

void		restaure_history_from_file(t_sh *sh)
{
	char	*str;
	int		i;
	t_inp	*inp;

	inp = NULL;
	while (get_next_line(sh->fd, &str))
	{
		i = -1;
		while (str[++i] && str[i] > 32 && str[i] < 127)
			inp_insert_posat(&inp, str[i]);
		if (inp)
			history_push_front(&sh->history, inp);
		free_list_from_beginning(&inp);
		free(str);
	}
}

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
