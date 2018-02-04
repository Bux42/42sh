/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 03:52:19 by videsvau          #+#    #+#             */
/*   Updated: 2018/02/04 18:32:25 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"
#include "../builtin/builtin.h"

int			pos_at(t_inp **inp, int prompt_size)
{
	t_inp	*cp;

	if ((cp = (*inp)))
	{
		while (cp)
		{
			prompt_size++;
			if (cp->pos == 2)
				return (prompt_size - 1);
			else if (cp->pos == 1)
				return (prompt_size);
			cp = cp->next;
		}
	}
	return (prompt_size);
}

int			check_dimentions(t_sh *sh)
{
	int		new_size;

	if (!(tgetent(NULL, TERM)))
		return (0);
	if ((new_size = tgetnum("co")) != sh->width)
	{
		if (new_size < sh->width)
		{
			if (sh->pos_at > new_size)
				sh->posy = sh->pos_at % new_size;
			if (sh->posy == 1)
			{
				ft_putchar(' ');
				ft_putstr(tgetstr("le", NULL));
			}
		}
		else
		{
			if (sh->pos_at > new_size)
				sh->posy = sh->pos_at % new_size;
			else
				sh->posy = sh->pos_at;
		}
	}
	return (1);
}

void		check_endline(t_sh *sh)
{
	if (sh->posy == sh->width)
	{
		sh->posy = 1;
		ft_putchar(' ');
		ft_putstr(tgetstr("le", NULL));
	}
	else
		sh->posy++;
}

void		treat_input(t_sh *sh)
{
	sh->pos_at = pos_at(&sh->inpl->inp, sh->prompt_len);
	if (!check_dimentions(sh))
		return ;
	sh->width = tgetnum("co");
	if (!sh->buff[1])
	{
		if (sh->buff[0] > 31 && sh->buff[0] <= 127)
		{
			add_delete_letter(sh);
			autocompletion(&sh->inpl->inp, sh);
		}
		else
			check_shortcut(sh);
	}
	if (sh->buff[0] == 4 && !sh->buff[1])
	{
		char *tab[3];
		tab[0] = "exit";
		tab[1] = "0";
		tab[2] = NULL;
		builtin_exit(tab, &sh->env);
	}
	if (!sh->buff[3] && sh->buff[0] == 27 && sh->buff[1] == 91)
		move_cursor(sh, &sh->inpl->inp, sh->buff[2]);
	if (sh->buff[0] == 27 && sh->buff[1] == 27 && sh->buff[2] == 91)
		jump_words(sh, sh->buff[3]);
	if (sh->buff[3] == 126 && sh->buff[2] == 51)
	{
		erase_completion(sh, &sh->inpl->inp);
		delete_after(sh, &sh->inpl->inp);
		autocompletion(&sh->inpl->inp, sh);
	}
	if (sh->inpl)
		sh->inp_len = inp_list_len(&sh->inpl->inp);
	if (sh->tty)
		tty_debug(sh, &sh->inpl->inp);
	free_comp(4, sh);
	ft_bzero(sh->buff, 6);
}
