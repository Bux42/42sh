/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_inp_a.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 16:24:53 by videsvau          #+#    #+#             */
/*   Updated: 2017/11/04 18:35:13 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

void		delete_last(t_inp **inp, t_inp *cp)
{
	(*inp) = NULL;
	free(*inp);
	free(cp);
}

void		delete_at_begining(t_inp **inp, t_inp *cp)
{
	(*inp) = (*inp)->next;
	(*inp)->previous = NULL;
	(*inp)->pos = 2;
	free(cp);
}

void		delete_middle(t_inp *cp)
{
	t_inp	*tmp;

	tmp = cp->next;
	if (tmp->next)
	{
		cp = tmp->next;
		cp->previous = tmp->previous;
		tmp->previous->next = cp;
	}
	else
		cp->next = NULL;
	free(tmp);
}

void		restaure_input_line_a(t_inp **inp)
{
	t_inp	*cp;
	int		i;

	i = 1;
	if ((cp = (*inp)))
	{
		while (cp->next)
		{
			i++;
			ft_putchar(cp->next->c);
			cp = cp->next;
		}
		ft_putchar(' ');
		while (i--)
			ft_putstr(tgetstr("le", NULL));
	}
}

void		delete_pos_a(t_inp **inp)
{
	t_inp	*cp;

	if ((cp = (*inp)))
	{
		while (cp)
		{
			if (cp->pos)
			{
				if (cp->pos == 1)
					restaure_input_line_a(&cp->next);
				else
					restaure_input_line_a(&cp);
				if (cp->next)
				{
					if (cp->pos == 2)
						delete_at_begining(inp, cp);
					else
						delete_middle(cp);
				}
				else if (cp->pos == 2)
					delete_last(inp, cp);
				return ;
			}
			cp = cp->next;
		}
	}
}
