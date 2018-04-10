/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_treat_input.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 09:10:03 by videsvau          #+#    #+#             */
/*   Updated: 2018/04/10 11:49:14 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"
#include "../builtin/builtin.h"

void		try_exit(t_sh *sh, t_inp **inp)
{
	char	*tab[3];

	if (!(*inp))
	{
		tab[0] = "exit";
		tab[1] = "0";
		tab[2] = NULL;
		builtin_exit(tab, sh);
	}
}

int			inpl_char_cmp(char *ending, t_inp **inp)
{
	t_inp	*cp;
	int		i;

	if ((cp = (*inp)))
	{
		i = 0;
		while (cp && ending[i])
		{
			if (cp->c == ending[i])
			{
				cp = cp->next;
				i++;
			}
			else
				break ;
			if (!cp && !ending[i])
				return (0);
		}
	}
	return (1);
}

int			check_pasted_here(t_sh *sh, t_inpl **inpl, char *ending)
{
	int		ret;
	int		i;
	char	tmp[6];

	i = -1;
	ret = 0;
	if (sh->buff[0] == 27 || sh->buff[1] == '\0')
		ret = treat_input_here(sh, inpl, ending);
	else
	{
		ft_bzero(tmp, 6);
		while (++i < 6)
			tmp[i] = sh->buff[i];
		ft_bzero(sh->buff, 6);
		i = -1;
		while (++i < 6)
		{
			sh->buff[0] = tmp[i];
			ret = treat_input_here(sh, inpl, ending);
			if (!ret)
				break ;
		}
	}
	return (ret);
}

void		classic_edition(t_inp **inp, t_sh *sh, int flag)
{
	if (flag & HERE)
	{
		if (sh->buff[0] != 127)
		{
			ft_putchar(sh->buff[0]);
			check_endline(sh);
			inp_insert_posat(inp, sh->buff[0]);
		}
		else
			delete_letter(g_sh, inp);
	}
	else
	{
		if (sh->buff[0] > 31)
		{
			add_delete_letter(sh);
			autocompletion(inp, sh);
		}
		else
			check_shortcut(sh);
	}
}

int			treat_input_here(t_sh *sh, t_inpl **inpl, char *ending)
{
	sh->pos_at = pos_at(&(*inpl)->inp, sh->prompt_len);
	if (!check_dimentions(sh))
		return (0);
	sh->width = tgetnum("co");
	if (!sh->buff[1])
	{
		if (sh->buff[0] > 31)
			classic_edition(&(*inpl)->inp, g_sh, HERE);
		else if (sh->buff[0] == 10)
		{
			if (!inpl_char_cmp(ending, &(*inpl)->inp))
				return (0);
			else
			{
				inp_insert_posat(&(*inpl)->inp, '\n');
				inpl_add_new(inpl, 0);
				print_heredoc(ending, sh);
			}
		}
	}
	sh->inp_len = inp_list_len(&(*inpl)->inp);
	if (sh->tty_fd != -1)
		tty_debug(sh, &(*inpl)->inp);
	return (1);
}
