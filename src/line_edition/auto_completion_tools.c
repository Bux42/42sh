/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_completion_tools.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drecours <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 14:56:37 by drecours          #+#    #+#             */
/*   Updated: 2018/04/10 16:06:31 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

void		check_if_dir(t_sh *sh, t_inp **inp)
{
	char		buff[5000];
	struct stat	st;

	ft_bzero(buff, 5000);
	ft_strcat(buff, sh->save_path);
	if (buff[ft_strlen(buff) -1] != '/')
		ft_strcat(buff, "/");
	ft_strcat(buff, sh->comp_debug);
	ft_strcat(buff, sh->comp_remain);
	if (lstat(buff, &st) != -1)
	{
		if (S_ISDIR(st.st_mode))
		{
			inp_insert_posat(inp, '/');
			ft_putchar('/');
			check_endline(sh);
		}
	}
}

void		insert_completion(t_sh *sh, t_inp **inp)
{
	t_inp	*cp;
	int		i;

	if (sh->comp_remain)
	{
		if ((cp = get_to_pos(inp)))
		{
			i = -1;
			while (sh->comp_remain[++i])
			{
				inp_insert_posat(&sh->inpl->inp, sh->comp_remain[i]);
				ft_putchar(sh->comp_remain[i]);
				check_endline(sh);
			}
			check_if_dir(sh, inp);
			overwrite_remaining(sh, &sh->inpl->inp);
		}
		free_comp(3, sh);
	}
}

void		do_shit(t_inp **inp)
{
	t_inp	*cp;

	cp = (*inp);
	while (cp)
	{
		ft_putchar_fd(cp->c, g_sh->tty_fd);
		cp = cp->next;
	}
}
