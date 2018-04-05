/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimized_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 21:58:15 by videsvau          #+#    #+#             */
/*   Updated: 2018/03/23 10:25:13 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

void		inp_insert_chain(t_inp **src, t_sh *sh)
{
	t_inp	*cp;

	cp = *src;
	while (cp)
	{
		if (!(sh->inpl->inp))
		{
			sh->inpl->inp = new_inp(cp->c);
			sh->inpl->inp->pos = 1;
		}
		else
		{
			sh->inpl->inp->pos = 0;
			sh->inpl->inp->next = new_inp(cp->c);
			sh->inpl->inp->next->previous = sh->inpl->inp;
			sh->inpl->inp = sh->inpl->inp->next;
			sh->inpl->inp->pos = 1;
		}
		cp = cp->next;
	}
	while (sh->inpl->inp->previous)
		sh->inpl->inp = sh->inpl->inp->previous;
}

void		restore_cursor_right(int nb, t_sh *sh)
{
	while (nb > sh->width)
	{
		nb -= sh->width;
		ft_putstr(tgetstr("do", NULL));
	}
	while (nb--)
	{
		custom_right(sh);
	}
}

void		restore_cursor_pos(int nb, t_sh *sh)
{
	while (nb > sh->width)
	{
		nb -= sh->width;
		ft_putstr(tgetstr("up", NULL));
	}
	while (nb--)
		custom_left(sh);
}

void		print_str(char *str, t_sh *sh)
{
	char	buff[sh->width + 1];
	int		i;
	int		j;

	i = -1;
	j = -1;
	ft_bzero(buff, sh->width + 1);
	while (str[++i])
	{
		buff[++j] = str[i];
		if (sh->posy == sh->width)
		{
			ft_putstr(buff);
			ft_bzero(buff, sh->width + 1);
			j = -1;
			ft_putchar(' ');
			ft_putstr(tgetstr("le", NULL));
			sh->posy = 1;
		}
		else
			sh->posy++;
	}
	ft_putstr(buff);
}

int			print_inp(t_inp *cp, t_sh *sh)
{
	char	buff[sh->width + 1];
	int		i;
	int		written;

	i = -1;
	written = 0;
	ft_bzero(buff, sh->width + 1);
	while (cp->next && (written++ > -1))
	{
		buff[++i] = cp->next->c;
		if (sh->posy == sh->width)
		{
			ft_putstr(buff);
			ft_bzero(buff, sh->width + 1);
			i = -1;
			ft_putchar(' ');
			ft_putstr(tgetstr("le", NULL));
			sh->posy = 1;
		}
		else
			sh->posy++;
		cp = cp->next;
	}
	ft_putstr(buff);
	return (written);
}
