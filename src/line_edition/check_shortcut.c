/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_shortcut.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 06:36:04 by videsvau          #+#    #+#             */
/*   Updated: 2017/11/14 13:39:00 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

char		*get_clipboard(t_inp *inp, int *dec, t_sh *sh)
{
	char	*ret;
	int		cp;

	*dec = 1;
	while (inp)
	{
		if (inp->next)
		{
			inp = inp->next;
			(*dec)++;
		}
		else
			break ;
	}
	if (!(ret = (char*)malloc(sizeof(char) * (*dec) + 1)))
		return (NULL);
	ret[(*dec)] = '\0';
	cp = (*dec);
	while (--cp > -1)
	{
		ft_putchar(' ');
		check_endline(sh);
		ret[cp] = inp->c;
		inp = inp->previous;
	}
	return (ret);
}

void		free_list_from_here(t_inp *cp)
{
	if (cp->next)
		free_list_from_here(cp->next);
	else
		free(cp);
}

void		free_list_from_beginning(t_inp **inp)
{
	if (*inp)
	{
		if ((*inp)->next)
			free_list_from_here((*inp)->next);
		free(*inp);
		(*inp) = NULL;
	}
}

void		cut_after(t_sh *sh, t_inp **inp)
{
	t_inp	*cp;
	int		dec;

	if ((cp = get_to_pos(inp)))
	{
		if (cp->next)
		{
			if (sh->clipboard)
				free(sh->clipboard);
			if (cp->pos == 1)
			{
				sh->clipboard = get_clipboard(cp->next, &dec, sh);
				free_list_from_here(cp->next);
				cp->next = NULL;
			}
			else
			{
				sh->clipboard = get_clipboard(cp, &dec, sh);
				free_list_from_beginning(inp);
			}
			while (dec--)
				custom_left(sh);
		}
	}
}

void		check_shortcut(t_sh *sh)
{
	if (sh->buff[0] == 11)
		cut_after(sh, &sh->inpl->inp);
	if (sh->buff[0] == 16 && sh->clipboard)
		paste_after(sh, &sh->inpl->inp);
	if (sh->buff[0] == 23)
		cut_before(sh, &sh->inpl->inp);
	if (sh->buff[0] == 10)
	{
		ft_putstr(tgetstr("do", NULL));
		ft_putstr(tgetstr("cr", NULL));
		ft_putstr("Oui ya juste l'edition de ligne");
		ft_putstr(tgetstr("do", NULL));
		ft_putstr(tgetstr("cr", NULL));
		free_list_from_beginning(&sh->inpl->inp);
		print_prompt(sh);
	}
}
