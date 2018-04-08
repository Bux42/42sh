/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tty_debug.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 05:07:52 by videsvau          #+#    #+#             */
/*   Updated: 2018/04/08 16:41:13 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

void		add_line_infos(int *pos, char *buff, t_sh *sh)
{
	opti_strcat(pos, buff, "posy: ", 0);
	custom_itoa(pos, buff, sh->posy);
	opti_strcat(pos, buff, " width: ", 0);
	custom_itoa(pos, buff, sh->width);
	opti_strcat(pos, buff, " prompt_len: ", 0);
	custom_itoa(pos, buff, sh->prompt_len);
	opti_strcat(pos, buff, " retval: ", 0);
	custom_itoa(pos, buff, sh->retval);
	opti_strcat(pos, buff, " pos_at: ", 0);
	custom_itoa(pos, buff, sh->pos_at);
	opti_strcat(pos, buff, " inp_len: ", 0);
	custom_itoa(pos, buff, sh->inp_len);
	opti_strcat(pos, buff, " comp: ", 0);
	opti_strcat(pos, buff, sh->comp_debug, 1);
	opti_strcat(pos, buff, " comp_remain: ", 0);
	opti_strcat(pos, buff, sh->comp_remain, 1);
	opti_strcat(pos, buff, " path: ", 0);
	opti_strcat(pos, buff, sh->comp_path, 1);
	opti_strcat(pos, buff, "\n", 0);
}

void		add_buff_expected(int *pos, char *buff, t_sh *sh)
{
	custom_itoa(pos, buff, sh->buff[0]);
	opti_strcat(pos, buff, " ", 0);
	custom_itoa(pos, buff, sh->buff[1]);
	opti_strcat(pos, buff, " ", 0);
	custom_itoa(pos, buff, sh->buff[2]);
	opti_strcat(pos, buff, " ", 0);
	custom_itoa(pos, buff, sh->buff[3]);
	opti_strcat(pos, buff, " ", 0);
	custom_itoa(pos, buff, sh->buff[4]);
	opti_strcat(pos, buff, "\n", 0);
}

void		add_inp(int *pos, char *buff, t_inp **inp)
{
	t_inp	*cp;

	if ((cp = (*inp)))
	{
		while (cp && (*pos) + 100 < TTY_MAX)
		{
			opti_strcat(pos, buff, &cp->c, 2);
			cp = cp->next;
		}
		opti_strcat(pos, buff, "\n", 0);
		cp = (*inp);
		while (cp && (*pos) + 100 < TTY_MAX)
		{
			custom_itoa(pos, buff, cp->pos);
			cp = cp->next;
		}
		opti_strcat(pos, buff, "\n", 0);
	}
}

void		tty_debug(t_sh *sh, t_inp **inp)
{
	char	buff[TTY_MAX];
	int		i;

	i = 0;
	opti_strcat(&i, buff, "echo \"", 0);
	add_line_infos(&i, buff, sh);
	add_buff_expected(&i, buff, sh);
	add_inp(&i, buff, inp);
	opti_strcat(&i, buff, "\" > ", 0);
	opti_strcat(&i, buff, sh->tty, 0);
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
