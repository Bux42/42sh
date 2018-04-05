/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_treat_input.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 09:10:03 by videsvau          #+#    #+#             */
/*   Updated: 2018/03/23 14:34:40 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

int			inpl_char_cmp(char *ending, t_inp **inp)
{
	t_inp	*cp;
	int		i;

	if ((cp = (*inp)))
	{
		i = 0;
		while (cp && ending[i])
		{
			if (cp->c == ending[i])
			{
				cp = cp->next;
				i++;
			}
			else
				break ;
			if (!cp && !ending[i])
				return (0);
		}
	}
	return (1);
}

int			treat_input_here(t_sh *sh, t_inpl **inpl, char *ending)
{
	sh->pos_at = pos_at(&(*inpl)->inp, sh->prompt_len);
	if (!check_dimentions(sh))
		return (0);
	sh->width = tgetnum("co");
	if (!sh->buff[1])
	{
		if (sh->buff[0] > 31)
		{
			if (sh->buff[0] != 127)
			{
				ft_putchar(sh->buff[0]);
				check_endline(sh);
				inp_insert_posat(&(*inpl)->inp, sh->buff[0]);
			}
			else
				delete_letter(g_sh, &(*inpl)->inp);
		}
		else if (sh->buff[0] == 10)
		{
			if (!inpl_char_cmp(ending, &(*inpl)->inp))
				return (0);
			else
			{
				inp_insert_posat(&(*inpl)->inp, '\n');
				inpl_add_new(inpl, 0);
				print_heredoc(ending, sh);
			}
		}
	}
	sh->inp_len = inp_list_len(&(*inpl)->inp);
	if (sh->tty)
		tty_debug(sh, &(*inpl)->inp);
	return (1);
}
