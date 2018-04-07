/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_screen.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 02:05:21 by videsvau          #+#    #+#             */
/*   Updated: 2018/04/07 02:45:27 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

void		print_inp_clear(t_inp **inp, t_sh *sh)
{
	t_inp	*cp;
	int		len;

	len = 0;
	if ((cp = (*inp)))
	{
		while (cp)
		{
			ft_putchar(cp->c);
			check_endline(sh);
			if (cp->next)
				cp = cp->next;
			else
				break ;
		}
		while (!cp->pos && cp->previous)
		{
			len++;
			cp = cp->previous;
		}
		if (cp->pos == 2)
			len++;
		while (len--)
			custom_left(sh);
	}
}

void		print_lines(t_inpl **inpl, t_close **close, t_sh *sh)
{
	t_inpl	*cp;

	if ((cp = (*inpl)))
	{
		while (cp->previous)
			cp = cp->previous;
		print_inp_clear(&cp->inp, sh);
		while (cp->next)
		{
			custom_return();
			if ((*close)->flag & QUOTE)
				print_str("quote> ", sh);
			else
				print_str("dquote> ", sh);
			print_inp_clear(&cp->next->inp, sh);
			cp = cp->next;
		}
	}
}

void		clear_screen(t_sh *sh)
{
	ft_putstr(tgetstr("cl", NULL));
	sh->posy = 1;
	print_prompt(sh);
	print_lines(&sh->inpl, &sh->close, sh);
}
