/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_completion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 20:43:59 by videsvau          #+#    #+#             */
/*   Updated: 2017/11/04 20:53:09 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

int			auto_completion(t_inp **inp)
{
	t_inp	*cp;

	if ((cp = (*inp)))
	{
		while (cp->next)
		{
			if (cp->pos)
				break ;
			cp = cp->next;
		}
		if (cp->previous && !is_space(cp->previous->c))
			return (1);
	}
	inp_push_back(inp, '\t');
	ft_putchar('\t');
	return (0);
}
