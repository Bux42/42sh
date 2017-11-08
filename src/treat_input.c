/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 20:25:37 by videsvau          #+#    #+#             */
/*   Updated: 2017/11/08 22:26:35 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../inc/header.h"

void		treat_input(t_sh *sh)
{
	/*ft_putnbr(sh->buff[0]);
	ft_putchar(' ');
	ft_putnbr(sh->buff[1]);
	ft_putchar(' ');
	ft_putnbr(sh->buff[2]);
	ft_putchar(' ');
	ft_putnbr(sh->buff[3]);
	ft_putchar(' ');
	ft_putnbr(sh->buff[4]);
	*/if (!sh->buff[1] && sh->buff[0] != 10 && sh->buff[0] != 9)
	{
		if (sh->buff[0] == 127)
			delete_pos(&sh->inp);
		else
		{
			ft_putchar(sh->buff[0]);
			inp_push_back(&sh->inp, sh->buff[0]);
		}
	}
	else
	{
		if (!sh->buff[1])
			;
		else if (sh->buff[0] == 27 && sh->buff[1] == 91)
		{
			if (sh->buff[2] == 68)
				move_left(&sh->inp);
			else if (sh->buff[2] == 67)
				move_right(&sh->inp);
			else if (sh->buff[2] == 51 && sh->buff[3] == 126 && !sh->buff[4])
				delete_pos_a(&sh->inp);
			else if (sh->buff[2] == 70 && !sh->buff[3])
				home_end(&sh->inp, 0);
			else if (sh->buff[2] == 72 && !sh->buff[3])
				home_end(&sh->inp, 1);
		}
		else if (sh->buff[0] == 27 && sh->buff[1] == 27 && sh->buff[2] == 91)
		{
			if (!sh->buff[4])
			{
				if (sh->buff[3] == 68)
					jump_left_word(&sh->inp);
				if (sh->buff[3] == 67)
					jump_right_word(&sh->inp);
			}
		}
	}
	debug_file(&sh->inp);
	ft_bzero(sh->buff, 6);
}
