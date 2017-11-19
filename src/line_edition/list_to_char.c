/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_to_char.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/19 15:48:39 by videsvau          #+#    #+#             */
/*   Updated: 2017/11/19 16:07:07 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

char		*inp_to_char(t_inp **inp, t_sh *sh)
{
	char	*ret;
	t_inp	*cp;
	int		i;

	if (!(cp = (*inp)))
		return (NULL);
	else
	{
		if (!(ret = (char*)malloc(sizeof(char) * (sh->inp_len + 1))))
			return (NULL);
		ret[sh->inp_len] = '\0';
		i = 0;
		while (cp)
		{
			ret[i] = cp->c;
			i++;
			cp = cp->next;
		}
	}
	return (ret);
}
