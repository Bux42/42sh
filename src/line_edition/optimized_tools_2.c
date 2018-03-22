/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimized_tools_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 08:30:04 by videsvau          #+#    #+#             */
/*   Updated: 2018/03/22 08:39:16 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

int			inp_to_inp_cmp(t_inp **inp1, t_inp **inp2)
{
	t_inp	*cp1;
	t_inp	*cp2;

	if ((cp1 = (*inp1)) && (cp2 = (*inp2)))
	{
		while (cp1 && cp2)
		{
			if (cp1->c != cp2->c)
				return (0);
			cp1 = cp1->next;
			cp2 = cp2->next;
		}
		if ((!cp1 && cp2) || (cp1 && !cp2))
			return (0);
	}
	return (1);
}
