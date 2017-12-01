/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_backquotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 07:30:31 by videsvau          #+#    #+#             */
/*   Updated: 2017/12/01 07:48:21 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

t_inp		*parse_backquotes(t_inpl **inpl, t_sh *sh)
{
	t_inpl	*cp;
	t_inp	*ret;

	ret = NULL;
	sh->posy = sh->posy;
	if ((cp = (*inpl)))
	{
		while (cp)
		{
			while (cp->inp)
			{
				inp_insert_posat(&ret, cp->inp->c);
				cp->inp = cp->inp->next;
			}
			cp = cp->next;
		}
	}
	return (ret);
}

void		parse(t_sh *sh)
{
	t_inp	*clean;

	clean = parse_backquotes(&sh->inpl, sh);
	while (clean)
	{
		ft_putchar(clean->c);
		clean = clean->next;
	}
	parse_backquotes(&sh->inpl, sh);
}
