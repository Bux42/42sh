/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_completion_tools.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drecours <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 14:56:37 by drecours          #+#    #+#             */
/*   Updated: 2018/04/09 14:56:59 by drecours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

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
				overwrite_remaining(sh, &sh->inpl->inp);
			}
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
