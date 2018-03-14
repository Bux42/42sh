/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exclaim_tools2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drecours <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 17:40:42 by drecours          #+#    #+#             */
/*   Updated: 2018/03/14 13:14:19 by drecours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "../../inc/header.h"

int		name_no_event(int i, t_inp *inp, int pos)
{
	ft_putstr("!: No such event: ");
	find_in_his(inp, inp, &i, pos);
	custom_return();
	return (-1);
}

int		no_event(int i)
{
	ft_putstr("!: No such event: ");
	ft_putnbr(i);
	custom_return();
	return (-1);
}

void	fill_str(t_inp *inp, char (*str)[20])
{
	int		i;

	i = 0;
	while (inp && inp->c && inp->c >= '0' && inp->c <= '9')
	{
		(*str)[i] = inp->c;
		inp = inp->next;
		i++;
	}
}
