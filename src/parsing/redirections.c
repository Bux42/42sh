/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 08:30:44 by videsvau          #+#    #+#             */
/*   Updated: 2017/12/12 08:42:30 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

int			redirection(t_inp **inp)
{
	t_inp	*cp;

	if ((cp = (*inp)))
	{
		if (cp->c == '>')
		{
			if (cp->next && cp->next->c == '>')
				ft_putstr(" append output to ");
			else
				ft_putstr(" redirect output to ");
			(*inp) = (*inp)->next;
		}
	}
	return (0);
}
