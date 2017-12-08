/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whats_going_on.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 17:55:43 by videsvau          #+#    #+#             */
/*   Updated: 2017/12/08 22:58:46 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

void		whats_going_on(t_inp **inp)
{
	t_inp	*cp;
	int		quote;
	int		dquote;

	quote = 0;
	dquote = 0;
	if ((cp = (*inp)))
	{
		while (cp)
		{
			if (cp->c == '\"' && !quote)
			{
				if (dquote)
				{
					ft_putchar(']');
					dquote = 0;
				}
				else
				{
					ft_putchar('[');
					dquote = 1;
				}
			}
			else if (cp->c == '\'' && !dquote)
			{
				if (quote)
				{
					ft_putchar(')');
					quote = 0;
				}
				else
				{
					ft_putchar('(');
					quote = 1;
				}
			}
			else
				ft_putchar(cp->c);
			cp = cp->next;
		}
		custom_return();
	}
}
