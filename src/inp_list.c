/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inp_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 20:32:41 by videsvau          #+#    #+#             */
/*   Updated: 2017/11/10 04:59:25 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

void		print_inp(t_inp **inp)
{
	t_inp	*cp;

	ft_putchar('\n');
	if (*inp)
	{
		cp = (*inp);
		while (cp)
		{
			ft_putnbr(cp->pos);
			ft_putchar(' ');
			//ft_putchar(cp->c);
			cp = cp->next;
		}
	}
}

t_inp		*new_inp(char c)
{
	t_inp	*ret;

	if (!(ret = (t_inp*)malloc(sizeof(t_inp))))
		return (NULL);
	ret->next = NULL;
	ret->previous = NULL;
	ret->c = c;
	ret->pos = 0;
	return (ret);
}

void		inp_push_back(t_inp **inp, char c)
{
	t_inp	*first;
	t_inp	*tmp;

	first = (*inp);
	tmp = NULL;
	if (!(*inp))
	{
		(*inp) = new_inp(c);
		(*inp)->pos = 1;
	}
	else
	{
		while (first->next)
		{
			if (first->pos)
			{
				tmp = new_inp(c);
				if (first->pos == 1)
				{
					first->next->previous = tmp;
					tmp->next = first->next;
					first->next = tmp;
					tmp->previous = first;
					tmp->pos = 1;
					first->pos = 0;
				}
				else
				{
					first->pos = 0;
					tmp->pos = 1;
					tmp->next = first;
					first->previous = tmp;
					(*inp) = tmp;
				}
				return ;
			}
			tmp = first;
			first = first->next;
		}
		tmp = new_inp(c);
		tmp->pos = 1;
		first->pos = 0;
		first->next = tmp;
		tmp->previous = first;
	}
}
