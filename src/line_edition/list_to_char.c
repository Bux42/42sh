/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_to_char.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/19 15:48:39 by videsvau          #+#    #+#             */
/*   Updated: 2018/03/23 10:32:59 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

char		*inp_to_cont(t_inp **inp)
{
	char	*ret;
	t_inp	*cp;
	int		len;

	ret = NULL;
	len = 0;
	if ((cp = (*inp)))
	{
		while (cp)
		{
			len++;
			cp = cp->next;
		}
		if (!(ret = (char*)malloc(sizeof(char) * (len + 1))))
			return (NULL);
		ret[len] = '\0';
		len = 0;
		cp = *inp;
		while (cp)
		{
			ret[len++] = cp->c;
			cp = cp->next;
		}
	}
	return (ret);
}

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
			ft_putchar(ret[i]);
			i++;
			cp = cp->next;
		}
	}
	return (ret);
}
