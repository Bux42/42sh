/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paste_after.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 09:34:40 by videsvau          #+#    #+#             */
/*   Updated: 2017/11/16 14:23:57 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

char		*get_clipboard_before(t_inp *inp, int *dec, t_sh *sh)
{
	char	*ret;
	int		cp;

	(*dec) = 0;
	while (inp)
	{
		custom_left(sh);
		(*dec)++;
		if (inp->previous)
			inp = inp->previous;
		else
			break ;
	}
	sh->retval = (*dec);
	if (!(ret = (char*)malloc(sizeof(char) * (*dec) + 1)))
		return (NULL);
	ret[(*dec)] = '\0';
	cp = -1;
	while (++cp < (*dec))
	{
		ret[cp] = inp->c;
		inp = inp->next;
	}
	return (ret);
}

void		free_list_before(t_inp *cp)
{
	if (cp->previous)
		free_list_before(cp->previous);
	else
		free(cp);
}

void		update_cut_before(int dec, t_inp **inp, t_sh *sh)
{
	t_inp	*cp;
	int		decp;
	int		remaining;

	remaining = 0;
	if ((cp = get_to_pos(inp)))
	{
		while (cp)
		{
			remaining++;
			ft_putchar(cp->c);
			check_endline(sh);
			cp = cp->next;
		}
	}
	decp = dec;
	while (dec--)
	{
		ft_putchar(' ');
		check_endline(sh);
	}
	while (decp--)
		custom_left(sh);
	while (remaining--)
		custom_left(sh);
}

void		cut_before(t_sh *sh, t_inp **inp)
{
	t_inp	*cp;
	int		dec;

	if ((cp = get_to_pos(inp)))
	{
		if (cp->pos == 1)
		{
			if (sh->clipboard)
				free(sh->clipboard);
			sh->clipboard = get_clipboard_before(cp, &dec, sh);
			if (cp->next)
			{
				cp = cp->next;
				free_list_before(cp);
				cp->previous = NULL;
				cp->pos = 2;
				(*inp) = cp;
			}
			else
			{
				free_list_before(cp);
				(*inp) = NULL;
			}
			update_cut_before(dec, inp, sh);
		}
	}
}

void		paste_after(t_sh *sh, t_inp **inp)
{
	int		i;

	i = -1;
	while (sh->clipboard[++i])
	{
		ft_putchar(sh->clipboard[i]);
		check_endline(sh);
		inp_insert_posat(inp, sh->clipboard[i]);
	}
	if (i > 0)
		overwrite_remaining(sh, inp);
}
