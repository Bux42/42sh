/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   home_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 11:27:36 by videsvau          #+#    #+#             */
/*   Updated: 2017/11/13 07:02:12 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

void		home_end(t_sh *sh, t_inp **inp, int active)
{
	t_inp	*cp;

	if ((cp = get_to_pos(inp)))
	{
		if (active == 1)
		{
			if (cp->pos == 2)
				custom_right(sh);
			cp->pos = 0;
			while (cp->next && custom_right(sh))
				cp = cp->next;
			cp->pos = 1;
		}
		else
		{
			if (cp->pos != 2)
				custom_left(sh);
			cp->pos = 0;
			while (cp->previous && custom_left(sh))
				cp = cp->previous;
			cp->pos = 2;
		}
	}
}
