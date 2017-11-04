/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drecours <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 16:16:52 by drecours          #+#    #+#             */
/*   Updated: 2017/10/31 16:21:08 by drecours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

int		quotes(t_inp *inp)
{
	int		i;
	char	c;

	i = 0;
	c = ' ';
	while (inp && inp->c)
	{
		if (inp->c == '\'' || inp->c == '\"')
		{
			c = inp->c;
			while (inp && inp->c && inp->c != c)
				inp = inp->next;
			if (inp->c != c)
			{
				if (c == '\'')
					ft_putstr("\nquote> ");
				else
					ft_putstr("\ndquote> ");
				return (0);
			}
		}
		if (inp->c == '\\' && !inp->next)
		{
			ft_putstr("\n> ");
			return (0);
		}
		inp = inp->next;
	}
	return (1);
}
