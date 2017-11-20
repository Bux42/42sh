/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tty_debug.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 05:07:52 by videsvau          #+#    #+#             */
/*   Updated: 2017/11/20 19:15:13 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

void		tty_debug(t_sh *sh, t_inp **inp)
{
	char	buff[20048];
	char	inpbuff[2];
	char	*itoa;
	t_inp	*cp;

	ft_bzero(buff, 2047);
	ft_strcat(buff, "echo ");
	ft_strcat(buff, " \"posy: ");
	ft_strcat(buff, ft_itoa(sh->posy));
	ft_strcat(buff, " width: ");
	ft_strcat(buff, ft_itoa(sh->width));
	ft_strcat(buff, " prompt_len: ");
	ft_strcat(buff, ft_itoa(sh->prompt_len));
	ft_strcat(buff, " retval: ");
	ft_strcat(buff, ft_itoa(sh->retval));
	ft_strcat(buff, " pos_at: ");
	ft_strcat(buff, ft_itoa(sh->pos_at));
	ft_strcat(buff, " inp_len: ");
	ft_strcat(buff, ft_itoa(sh->inp_len));
	ft_strcat(buff, " history_len: ");
	ft_strcat(buff, ft_itoa(sh->history_len));
	ft_strcat(buff, " completion: ");
	if (sh->comp_debug)
		ft_strcat(buff, sh->comp_debug);
	else
		ft_strcat(buff, "NULL");
	ft_strcat(buff, " remain: ");
	if (sh->comp_remain)
		ft_strcat(buff, sh->comp_remain);
	else
		ft_strcat(buff, "NULL");
	if (sh->clipboard)
	{
		ft_strcat(buff, " Clipboard: ");
		ft_strcat(buff, sh->clipboard);
	}
	ft_strcat(buff, "\n");itoa = ft_itoa(sh->buff[0]);ft_strcat(buff, itoa);free(itoa);
	ft_strcat(buff, " ");itoa = ft_itoa(sh->buff[1]);ft_strcat(buff, itoa);free(itoa);
	ft_strcat(buff, " ");itoa = ft_itoa(sh->buff[2]);ft_strcat(buff, itoa);free(itoa);
	ft_strcat(buff, " ");itoa = ft_itoa(sh->buff[3]);ft_strcat(buff, itoa);free(itoa);
	ft_strcat(buff, " ");itoa = ft_itoa(sh->buff[4]);ft_strcat(buff, itoa);free(itoa);
	ft_strcat(buff, "\n");
	if ((cp = (*inp)))
	{
		inpbuff[1] = '\0';
		while (cp)
		{
			inpbuff[0] = cp->c;
			ft_strcat(buff, inpbuff);
			cp = cp->next;
		}
	}
	ft_strcat(buff, "\n");
	if ((cp = (*inp)))
	{
		while (cp)
		{
			inpbuff[0] = cp->pos + 48;
			ft_strcat(buff, inpbuff);
			cp = cp->next;
		}
	}
	ft_strcat(buff, "\n");
	ft_strcat(buff, "\" > ");
	ft_strcat(buff, sh->tty);
	system(buff);
}

int			get_tty(t_sh *sh, char *av)
{
	struct stat	st;

	if (av && lstat(av, &st) > -1)
		sh->tty = ft_strdup(av);
	else
		sh->tty = NULL;
	return (1);
}
