/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tty_debug.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 05:07:52 by videsvau          #+#    #+#             */
/*   Updated: 2018/02/04 19:00:17 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

int			special_char(char c)
{
	if (c == '\"')
		return (1);
	if (c == '`')
		return (1);
	if (c == '\\')
		return (1);
	return (0);
}

char		*custom_strcat(char *s1, char *s2)
{
	short	i;
	short	j;

	i = 0;
	j = 0;
	while (s1[i])
		i++;
	while (s2[j])
	{
		if (special_char(s2[j]))
		{
			s1[i] = '\\';
			i++;
		}
		s1[i] = s2[j];
		i++;
		j++;
	}
	s1[i] = '\0';
	return (s1);
}

void		tty_debug(t_sh *sh, t_inp **inp)
{
	char	buff[20048];
	char	inpbuff[2];
	char	*itoa;
	t_inp	*cp;

	ft_bzero(buff, 2047);
	custom_strcat(buff, "echo ");
	ft_strcat(buff, " \"posy: ");
	itoa = ft_itoa(sh->posy);custom_strcat(buff, itoa);free(itoa);
	custom_strcat(buff, " width: ");
	itoa = ft_itoa(sh->width);custom_strcat(buff, itoa);free(itoa);
	custom_strcat(buff, " prompt_len: ");
	itoa = ft_itoa(sh->prompt_len);custom_strcat(buff, itoa);free(itoa);
	custom_strcat(buff, " retval: ");
	itoa = ft_itoa(sh->retval);custom_strcat(buff, itoa);free(itoa);
	custom_strcat(buff, " pos_at: ");
	itoa = ft_itoa(sh->pos_at);custom_strcat(buff, itoa);free(itoa);
	custom_strcat(buff, " inp_len: ");
	itoa = ft_itoa(sh->inp_len);custom_strcat(buff, itoa);free(itoa);
	custom_strcat(buff, " history_len: ");
	itoa = ft_itoa(sh->history_len);custom_strcat(buff, itoa);free(itoa);
	custom_strcat(buff, " completion: ");
	if (sh->comp_debug)
		custom_strcat(buff, sh->comp_debug);
	else
		custom_strcat(buff, "NULL");
	custom_strcat(buff, " remain: ");
	if (sh->comp_remain)
		custom_strcat(buff, sh->comp_remain);
	else
		custom_strcat(buff, "NULL");
	custom_strcat(buff, " path: ");
	if (sh->comp_path)
		custom_strcat(buff, sh->comp_path);
	else
		custom_strcat(buff, "NULL");
	if (sh->clipboard)
	{
		custom_strcat(buff, " Clipboard: ");
		custom_strcat(buff, sh->clipboard);
	}
	ft_strcat(buff, " diff: ");
	itoa = ft_itoa(sh->diff);
	ft_strcat(buff, itoa);
	free(itoa);
	ft_strcat(buff, "\n");itoa = ft_itoa(sh->buff[0]);custom_strcat(buff, itoa);free(itoa);
	custom_strcat(buff, " ");itoa = ft_itoa(sh->buff[1]);custom_strcat(buff, itoa);free(itoa);
	custom_strcat(buff, " ");itoa = ft_itoa(sh->buff[2]);custom_strcat(buff, itoa);free(itoa);
	custom_strcat(buff, " ");itoa = ft_itoa(sh->buff[3]);custom_strcat(buff, itoa);free(itoa);
	custom_strcat(buff, " ");itoa = ft_itoa(sh->buff[4]);custom_strcat(buff, itoa);free(itoa);
	ft_strcat(buff, "\n");
	ft_strcat(buff, "expected esc char: ");
	if (sh->expected_quote == '\0')
		ft_strcat(buff, "None");
	else
		custom_strcat(buff, &sh->expected_quote);
	ft_strcat(buff, "\n");
	if ((cp = (*inp)))
	{
		inpbuff[1] = '\0';
		while (cp)
		{
			inpbuff[0] = cp->c;
			custom_strcat(buff, inpbuff);
			cp = cp->next;
		}
	}
	ft_strcat(buff, "\n");
	if ((cp = (*inp)))
	{
		while (cp)
		{
			inpbuff[0] = cp->pos + 48;
			custom_strcat(buff, inpbuff);
			cp = cp->next;
		}
	}
	ft_strcat(buff, "\n");
	ft_strcat(buff, "search_his: ");
	itoa = ft_itoa(sh->search);
	ft_strcat(buff, itoa);
	free(itoa);
	ft_strcat(buff, " failed search?: ");
	itoa = ft_itoa(sh->failed_search);
	ft_strcat(buff, itoa);
	free(itoa);
	ft_strcat(buff, "\n");
	ft_strcat(buff, "\" > ");
	custom_strcat(buff, sh->tty);
	system(buff);
}

int			get_tty(t_sh *sh, char *av)
{
	struct stat	st;

	if (av && lstat(av, &st) > -1)
	{
		if (S_ISCHR(st.st_mode) && ft_strlen(av) == 12)
			sh->tty = ft_strdup(av);
		else
			sh->tty = NULL;
	}
	else
		sh->tty = NULL;
	return (1);
}
