/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 20:52:10 by videsvau          #+#    #+#             */
/*   Updated: 2018/04/11 12:14:02 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

t_inp		*inp_insert_chain_his(t_inp **src, t_sh *sh, int nb)
{
	t_inp	*ret;
	t_inp	*cp;

	ret = NULL;
	if ((cp = (*src)))
	{
		while (cp && nb--)
		{
			if (cp->c != '\n')
			{
				if (!sh->hist_res)
					write(sh->fd, &cp->c, 1);
				inp_insert_posat(&ret, cp->c);
			}
			cp = cp->next;
		}
	}
	return (ret);
}
