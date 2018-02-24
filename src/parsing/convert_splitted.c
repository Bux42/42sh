/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_splitted.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 15:59:20 by videsvau          #+#    #+#             */
/*   Updated: 2018/02/24 16:24:38 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

void		convert_content(t_inp **inp, t_sh *sh)
{
	t_inp	*cp;

	sh->posy = sh->posy;
	if ((cp = (*inp)))
	{
		while (cp)
			cp = cp->next;
	}
}

int			identify_tok(t_inp **inp)
{
	int		type;
	t_inp	*cp;

	type = 0;
	if ((cp = (*inp)))
	{
		while (cp)
			cp = cp->next;
	}
	return (type);
}

void		convert_splitted(t_inpl **inpl, t_sh *sh)
{
	t_inpl	*cp;

	sh->posy = sh->posy;
	if ((cp = (*inpl)))
	{
		while (cp)
		{
			convert_content(&cp->inp, sh);
			cp->type = identify_tok(&cp->inp);
			cp = cp->next;
		}
	}
}
